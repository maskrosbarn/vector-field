# vector-field

Given a vector:

$$\overrightarrow{a}\left ( x, y \right ) = \begin{bmatrix} f\left ( x, y \right )\\
g\left ( x, y \right ) \end{bmatrix}$$

where $f$ and $g$ are arbitrary functions.  At fixed intervals on $x$ and $y$, we normalise and plot:

$$\begin{bmatrix}x\\
y\end{bmatrix} + \overrightarrow{a}\left ( x, y \right )$$

When running the program, the axes are draggable, and zooming can be done with the mouse wheel.

The functions $f$ and $g$ can be any function which will be used to determine the behaviour of the vector field in the x- and y-directions, respectively; in the demonstration below, the chosen functions are the equations of motion of a pendulum where we rename the x - y plane as the $\theta$ - $v$ plane representing the angular position and velocity, respectively, of a pendulum under gravity.

$$f\left ( x, y \right )=f\left ( \theta, v \right )=v$$

$$g\left ( x, y \right )=g\left ( \theta, v \right )=-\mu v - \frac{g}{L} sin \left ( \theta \right )$$

Thus, making the diagram below a phase portrait of a pendulum showing the state evolution of the system with length $L$ under gravitional acceleration $g$ with a drag coeffient $\mu$.

Given that $f$ represents a displacement $\theta \left ( t \right )=...$, $g$, the velocity, is then $\frac{d\theta \left ( t \right )}{dt}=...$ for which Runge-Kutta approximation is used to update the position of each particle on the screen for the small time difference between the rendering of frames.

My computer could handle a few thousand particles on screen, but maybe offloading the Runge-Kutta calculations onto the GPU would improve that? I planned on doing just that through use of the OpenCL platform/library... [todo: add OpenCL support 🗿]

![](https://github.com/maskrosbarn/vector-field/blob/main/demo.gif)
