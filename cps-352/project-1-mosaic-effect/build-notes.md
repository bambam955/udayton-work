# CPS 352 Notes

This class uses the OpenCV library for C++.

To use it properly within Visual Studio, you have to configure some things project by project.

## Steps

1. Open your solution (open the `.sln` file) in Visual Studio.
2. Go to **Projects > <project-name> Properties**.
3. Open the **C/C++ > General** settings.
4. Add `<opencv-lib-loc>\opencv\build\include` to the **Additional Library Includes** setting.
5. Next, open the **Linker > General** settings.
6. Add `<opencv-lib-loc>\opencv\build\x64\vc16\lib` to the **Additional Library Directories** setting.
7. Next, open the **Linker > Input** settings.
8. Add `opencv_world4110d.lib` to the **Additional Dependencies** setting.
9. Build and run the project once to create the build directory (should be `<sln-directory\x64\Debug`).
10. Copy the file `opencv_world4110d.dll` from `<opencv-lib-loc>\opencv\build\x64\vc16\bin` to your build directory.
11. Run the project again. It should work fine this time.
