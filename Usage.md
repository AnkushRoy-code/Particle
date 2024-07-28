# Usage Guide - Particle Simulation

## Features Overview

### Menu Options
- **Quit Button:** Closes the application.

### Global Variables
- **Radius:** Adjust the Radius of the particles using the slider.
- **Particle Count:** Adjust the number of particles using the slider. Changes take effect once you release the slider. The minimum number of particles is 10, and the maximum is 1000.
- **Types Of Color:** Adjust the types/colors of particles using the slider. Changes take effect once you release the slider. The minimum number of particle types/colors is 2, and the maximum is 8.
- **Refresh:** Refreshes the simulation with the current settings.

### Distance Controls
- **Show MinDist Control:** Displays a foldable section to set the minimum distance for each particle type/color.
- **Same Min Dist:** Sets the minimum distance for all particle types/colors to the same value using a slider. The minimum value is 1 and the maximum is 30.
- **Show MaxDist Control:** Displays a foldable section to set the maximum distance for each particle type/color.
- **Same Max Dist:** Sets the maximum distance for all particle types/colors to the same value using a slider. The minimum value is 150 and the maximum is 300.

### Focus Control Settings
- **Buttons:**
  - **Random Forces:** Sets random forces for each particle type/color.
  - **Reset Forces:** Resets the forces for each particle type/color to 0.
  - **Minimise Force:** Sets the forces for each particle type/color to -1.
  - **Maximise Force:** Sets the forces for each particle type/color to 1.
  - **Default Force:** Sets predefined force values.
- **Save Forces to File:** Saves the current forces to a file named `forces.txt`.
- **Sliders:** Manually set individual forces for each particle type/color against other particle types/colors.

### Minimum Distance Control (If Enabled)
- **Buttons:**
  - **Random Min Dist:** Sets random minimum distances for each particle type/color.
  - **Minimise Dist:** Sets the minimum distances to 1.
  - **Maximise Dist:** Sets the minimum distances to 20.
  - **Default Dist:** Sets predefined minimum distances.
  - **Save Dist to File:** Saves the current minimum distances to a file `minDist.txt`.
- **Sliders:** Manually set minimum distances for each particle type/color. The minimum value is 1 and the maximum is 30.

### Maximum Distance Control (If Enabled)
- **Buttons:**
  - **Random Max Dist:** Sets random maximum distances for each particle type/color.
  - **Minimise Dist:** Sets the maximum distances 150.
  - **Maximise Dist:** Sets the maximum distances 300.
  - **Default Dist:** Sets predefined maximum distances.
  - **Save Dist to File:** Saves the current maximum distances to a file `maxDist.txt`.
- **Sliders:** Manually set maximum distances for each particle type/color. The minimum value is 150 and the maximum is 300.
