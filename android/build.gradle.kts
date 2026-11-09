// print-engine-android: Android library module that packs the program, Gutenprint's data and the
// printer table.
// Copyright (C) 2026 Petar Popov
// GPL-2.0-or-later; see README.md and COPYING.
//
// The module is built inside the consuming app's Gradle build (the app adds this repository as a
// git submodule and includes this directory as a project), so the Android Gradle plugin version
// comes from that build. It holds no code that runs in the app's process: the program is a native
// library file that the app starts as its own process, the data is an asset and the table is a
// resource.

plugins {
    id("com.android.library")
}

android {
    namespace = "io.github.pdimpopov.printengine"
    compileSdk = 37
    // scripts/build-android.sh builds with the NDK this line names.
    ndkVersion = "27.2.12479018"

    defaultConfig {
        // scripts/build-android.sh builds for the API level this line names.
        minSdk = 26
        ndk {
            // Release builds ship arm64-v8a only; debug builds add x86_64 below.
            abiFilters += "arm64-v8a"
        }
        externalNativeBuild {
            cmake {
                arguments += listOf(
                    "-DANDROID_STL=none",
                    "-DANDROID_SUPPORT_FLEXIBLE_PAGE_SIZES=ON",
                )
                // The program, libprintengine.so; it links libgutenprint statically.
                targets += "print-engine"
            }
        }
    }

    buildTypes {
        debug {
            ndk {
                // x86_64 runs the program on the emulator.
                abiFilters += "x86_64"
            }
        }
    }

    externalNativeBuild {
        cmake {
            path = file("../CMakeLists.txt")
            version = "3.22.1"
        }
    }
}

/**
 * Runs a Python step of this repository, `python3 -I SCRIPT INPUT [FILE]... OUTPUT`, where the FILEs
 * are [argumentFiles] in order and OUTPUT is [outputPath] under [outputDirectory]. The output directory
 * is emptied first, so a file that a new input no longer gives does not linger.
 */
@CacheableTask
abstract class PythonStep : DefaultTask() {
    @get:InputFile
    @get:PathSensitive(PathSensitivity.NONE)
    abstract val script: RegularFileProperty

    @get:InputDirectory
    @get:PathSensitive(PathSensitivity.RELATIVE)
    abstract val input: DirectoryProperty

    /** Files the script reads after [input], given in this order; none by default. */
    @get:InputFiles
    @get:PathSensitive(PathSensitivity.NONE)
    abstract val argumentFiles: ConfigurableFileCollection

    /** Where in [outputDirectory] the script writes; empty for the directory itself. */
    @get:Input
    abstract val outputPath: Property<String>

    @get:OutputDirectory
    abstract val outputDirectory: DirectoryProperty

    @get:Inject
    abstract val exec: ExecOperations

    @get:Inject
    abstract val fileSystem: FileSystemOperations

    @TaskAction
    fun run() {
        fileSystem.delete { delete(outputDirectory) }
        val output = outputDirectory.get().asFile
        output.mkdirs()
        exec.exec {
            commandLine(
                listOf("python3", "-I", script.get().asFile, input.get().asFile) + argumentFiles.files +
                    output.resolve(outputPath.get()),
            )
        }
    }
}

/** The asset directory that holds Gutenprint's data, the directory STP_DATA_PATH names. */
val dataAsset = "printengine"

// Gutenprint's data for every printer family, as the asset directory printengine/.
val printEngineData = tasks.register<PythonStep>("printEngineData") {
    script = layout.projectDirectory.file("../scripts/build-data.py")
    input = layout.projectDirectory.dir("../third_party/gutenprint/src/xml")
    outputPath = dataAsset
    outputDirectory = layout.buildDirectory.dir("generated/printengine/assets")
}

// The resources the data gives: xml/print_engine_printers, the (MFG, MDL) table of the printers
// the data drives, without the drivers that have none of A4, A5 and Letter, and the string
// print_engine_data_version, which names a copy of the data.
val printEngineResources = tasks.register<PythonStep>("printEngineResources") {
    script = layout.projectDirectory.file("../scripts/generate-resources.py")
    val asset = dataAsset
    input = printEngineData.flatMap { it.outputDirectory.dir(asset) }
    argumentFiles.from(layout.projectDirectory.file("../scripts/drivers-without-a4-a5-letter.txt"))
    outputPath = ""
    outputDirectory = layout.buildDirectory.dir("generated/printengine/res")
}

androidComponents {
    onVariants { variant ->
        variant.sources.assets?.addGeneratedSourceDirectory(printEngineData, PythonStep::outputDirectory)
        variant.sources.res?.addGeneratedSourceDirectory(printEngineResources, PythonStep::outputDirectory)
    }
}
