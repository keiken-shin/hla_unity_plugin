# HLA Plugin

### 🛠️ How to setup?

1. Install PitchRTI and its starter kit from its [website](https://pitchtechnologies.com/hlatutorial/).

2. Install [SimGe](https://user.ceng.metu.edu.tr/~otopcu/simge/) FOM generator app.

3. To run & compile C++ code we need gcc compiler. [Download here](https://sourceforge.net/projects/mingw-w64/). Also, [CMake](https://cmake.org/download/) package is needed.

4. Visual Studio with Visual Studio 2017 (VC141) platform toolset and Windows 10.xx SDK - For building `.dll` file.

5. Make sure that all the paths to pitchRTI, GCC compiler & CMake are set in system environment.

### 🏗️ Build the project

1. Create a `build/` folder & change directory to it.
    ```sh
    mkdir build && cd build
    ```

2. Next compile the project and create a `.sln` file.
    ```sh
    cmake ../
    ```
    **Note:** In the above mentioned command `../` is the path where `CMakeLists.txt` file is present, which refers to the c++ files.

3. Open `.sln` file in VS from the `build/` directory. In this case it will be `FlightSim.sln`, as this name is provided in CMakeList.

4. In visual studio under `FlightSim` solution, select `hla_plugin` and go to 
    - Project > Properties
    - Under Configuration Properties > General > Windows SDK Version, select Windows 10.xx SDK
    - Set Build to `Release -> 64` and build `hla_plugin`.
    - Inside `build/Release` folder, you will get the `.dll` file of the project.

Done, now use the `.dll` file in you Unity app 😊👌.

>💡 Note: For detail setup and working view [Documentation.md](./Documentation/Documentation.md)