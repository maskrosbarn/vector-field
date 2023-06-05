# vector-field

To do: finish me

Given a vector:

$$\overrightarrow{a}\left ( x, y \right ) = \begin{bmatrix} f\left ( x, y \right )\\
g\left ( x, y \right ) \end{bmatrix}$$

where $f$ and $g$ are arbitrary functions.  At fixed intervals on $x$ and $y$, we normalise and plot:

$$\begin{bmatrix}x\\
y\end{bmatrix} + \overrightarrow{a}\left ( x, y \right )$$

When running the program, the axes are draggable, and zooming can be done with the mouse wheel.

The functions $f$ and $g$ can be any function which will be used to determine the behaviour of the vector field in the x- and y-directions, respectively; in the demonstration below, the chosen functions are the equations of motion of a pendulum where we rename the x - y plane as the $\theta$ - $v$ plane representing the angular position and velocity, respectively, of a pendulum under gravity.

$$f\left ( x, y \right )=f\left ( \theta, v \right )=$$

![](https://github.com/maskrosbarn/vector-field/blob/main/demo.gif)
