# Particle Simulation - Usage Guide

## Features Overview

### Menu Options
- **Quit Button:** Closes the application.

### Global Variables
- **Radius:** Adjust the Radius of the particles using the slider.
- **Particle Count:** Adjust the number of particles using the slider. Changes take effect once you release the slider.
- **Types Of Color:** Adjust the types/colors of particles using the slider. Changes take effect once you release the slider.
- **Refresh:** Refreshes the simulation with the current settings.

### Distance Controls
- **Show MinDist Control:** Displays a foldable section to set the minimum distance for each particle type/color.
- **Same Min Dist:** Sets the minimum distance for all particle types/colors to the same value using a slider.
- **Show MaxDist Control:** Displays a foldable section to set the maximum distance for each particle type/color.
- **Same Max Dist:** Sets the maximum distance for all particle types/colors to the same value using a slider.

### Focus Control Settings
- **Buttons:**
  - **Random Forces:** Sets random forces for each particle type/color.
  - **Reset Forces:** Resets the forces for each particle type/color to 0.
  - **Minimise Force:** Sets the forces for each particle type/color to -1.
  - **Maximise Force:** Sets the forces for each particle type/color to 1.
  - **Default Force:** Sets predefined force values.
- **Save Forces to File:** Saves the current forces to a file named `forces.txt`.
- **Sliders:** Manually set individual forces for each particle type/color against other particle types/colors.

### Minimum/Maximum Distance Control (If Enabled)
- **Buttons:**
  - **Random Min/Max Dist:** Sets random min/max distances for each particle type/color.
  - **Minimise Dist:** Sets the min/max distances to their minimum values.
  - **Maximise Dist:** Sets the min/max distances to their maximum values.
  - **Default Dist:** Sets predefined min/max distances.
  - **Save Dist to File:** Saves the current min/max distances to a file.
- **Sliders:** Manually set min/max distances for each particle type/color.
