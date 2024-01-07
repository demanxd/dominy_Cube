plugins {
    id("com.android.application")
}

var sample = parent?.getName()

android {
    namespace = "com.demanxd.cube"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.demanxd.cube"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                cppFlags += "-std=c++14"
            }
        }
    }

    buildTypes {
        debug {
            externalNativeBuild {
                cmake {
                    arguments ("-DANDROID_TOOLCHAIN=clang",
                        "-DANDROID_STL=c++_static",
                        "-DANDROID_ARM_MODE=arm",
                        "-DANDROID_NATIVE_API_LEVEL=23",
                        "-DANDROID_CPP_FEATURES=exceptions",
                        "-DFILTER_TARGET=${sample}".toString(),
                        "-DCMAKE_BUILD_TYPE=Debug")

                    targets ("${sample}".toString())
                }
            }
        }
        release {
            externalNativeBuild {
                cmake {
                    arguments ("-DANDROID_TOOLCHAIN=clang",
                    "-DANDROID_STL=c++_static",
                    "-DANDROID_ARM_MODE=arm",
                    "-DANDROID_NATIVE_API_LEVEL=23",
                    "-DANDROID_CPP_FEATURES=exceptions",
                    "-DFILTER_TARGET=${sample}".toString(),
                    "-DCMAKE_BUILD_TYPE=RelWithDebInfo")

                    targets ("${sample}".toString())
                }
            }
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
    buildFeatures {
        viewBinding = true
    }
}

dependencies {

    implementation("androidx.appcompat:appcompat:1.6.1")
    implementation("com.google.android.material:material:1.11.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
}
