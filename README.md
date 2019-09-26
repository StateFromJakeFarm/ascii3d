# 3D First Person Environment Rendered with ASCII
---

![demo](demo.gif)

A program to render a 3D environment using only ASCII characters built entirely with C++11 using [ncurses 6.1](https://www.gnu.org/software/ncurses/ncurses.html) for UNIX systems (though I've only tested this on Ubuntu 18.04).

This project was inspired by and almost completely ripped off from javidx9's very cool tutorial [video](https://www.youtube.com/watch?v=xW8skO7MFYw).  The only major differences are the OOP approach in this rendition, and a simplified corner-detection method.

## Running the Program
To build and run this program, you will need the following installed on your Linux machine:

* g++ 7.4.0
* GNU Make 4.1
* ncurses 6.1
* terminal emulator supporting extended ASCII character set (ex: `konsole`)

### Step 1: Build executable
Navigate to the repository and enter the following command:
```
$ make
```

### Step 2: Adjust terminal dimensions
Adjust your terminal dimensions (rows x columns) to the desired "resolution."  Zooming out will increase both resolution and computing resources required to run the program, while zooming in will do the opposite.


### Step 3: Run executable
Enter the following command:
```
$ ./game sample_map.txt
```

### Step 4: End program
End the program at any time by pressing `Q`.

## Controls
Move character with WASD, turn character with left and right arrow keys.  Please note that only one input can be processed at a time due to limitations of ncurses.  I hope to find a workaround, but for now just be aware that pressing `W` and `A` will not result in diagonal movement.