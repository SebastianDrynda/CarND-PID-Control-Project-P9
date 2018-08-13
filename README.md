# Project CarND-PID-Control-Project-P9 
Udacity Self-Driving Car Engineer Nanodegree - CarND-PID-Control-Project

---

## Implementation

### The PID procedure follows what was taught in the lessons.

The PID implementation is done on the [./src/PID.cpp](./src/PID.cpp). The [PID::UpdateError](./src/PID.cpp#L33) method calculates proportional, integral and derivative errors and the [PID::TotalError](./src/PID.cpp#L49) calculates the total error using the appropriate coefficients.

## Reflection

### How PID control works

PID controllers are quite short to implement in code, but some knowledge for their parameters and characteristics are required to tune them properly in order to get a satisfactory result.

The parameters work as following:

- Kp is the coefficient representing the 'proportional' (P) part of the PID controller. In our case, the car Cross-Track Error (CTE) for a given step is multiplied by negative Kp, in order to provide a steering output proportional to the CTE. What this means is that a greater CTE will induce a sharper turn towards the desired trajectory.
- Kd is the coefficient representing the 'derivative' (D) part of the PID controller. The Kd is multiplied by the difference of the last two CTEs (in other words, the rate of change in the CTE). A negative change in successive CTE measurements (driving towards the desired trajectory) will dampen/smoothen the turn towards the desired trajectory, but a greater change in successive CTE measurements will provoke a sharper turn towards the trajectory. A properly tuned Kd (or derivative part) balances the proportional part in a way, effectively damping/smoothing the oscillations caused by the proportional control part.
- Ki is the coefficient representing the 'integral' (I) part of the PID controller. We use Ki to correct long-term drifts to the left or right of a lane, by multiplying Ki to the sum of all the CTEs from the beginning to the present moment. Deviations occuring for a longer period of time will (with time) be corrected (i.e. constantly driving to the left of the track inside the simulator will be corrected faster, as the sum of all CTE errors increases.


### Describe the effect each of the P, I, D components had in your implementation.

- The proportional portion of the controller tries to steer the car toward the center line (against the cross-track error). If used alone, the car overshoots the central line very easily and go out of the road very quickly. An example video where this component is used along is [./videos/only-proportional.mov](./videos/only-proportional.mov).
- The integral portion tries to eliminate a possible bias on the controlled system that could prevent the error to be eliminated. If used alone, it makes the car to go in circles. In the case of the simulator, no bias is present. An example video where this component is used along is [./videos/only-integral.mov](./videos/only-integral.mov).
- The differential portion helps to counteract the proportional trend to overshoot the center line by smoothing the approach to it. An example video where this component is used alone is [./videos/only-differential.mov](./videos/only-differential.mov).

### Describe how the final hyperparameters were chosen.

The parameters were chosen by manual tuning (try and error method): 
- First, make sure the car can drive straight with zero as parameters. 
- Then add the proportional and the car start going on following the road but it starts overshooting go out of it. 
- Then add the differential to try to overcome the overshooting. 
- The integral part only moved the car out of the road; so, it set very small. 
- After the car drove the track without going out of it, the parameters increased to minimize the average cross-track error on a single track lap. 
- The final parameters where Kp: 0.12, Ki: 0.00001, Kd: 2.1.

Next optimization steps (not implemented yet):
- Implement velocity PID Controller that controls the throttle value
- Implement steering and velocity PID controllers in relation to each other
- Implement twiddle method to find out hyperparameters

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

