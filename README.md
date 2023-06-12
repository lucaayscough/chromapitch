# Chroma

Chroma Audio main repository.

Here you can find the code to Chroma Pitch.

## To Build

To build on Mac OS:

Open terminal and install cmake:

```
brew install cmake
```

Clone the repo:

```
git clone https://github.com/chromaaudio/Chroma.git
```

Move to the cloned directory:

```
cd move/to/cloned/directory
```

```
mkdir build
```

```
cd build
```

Run cmake configuration:

```
cmake ..
```

Run generated make file:

```
make
```

The generated plugins and standalone can be found in the build folder.
VST3 and AU plugins should be automatically installed in:

``
~/Libary/Audio/Plug-ins/
``

This hasn't been tested on Windows and Linux, but should theoretically work the same.