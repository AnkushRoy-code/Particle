# 🎮 Usage Guide - Particle Simulation 🎮

**TL;DR:** smashing the "Random Forces" under the Force control section might be all that you need (My goto move). If you're into fine-tuning, explore the sliders.

Welcome to the Particle Simulation! Here's how to get the most out of your simulation experience.

## 🚀 Features Overview

### 🎨 Global Variables
- **🌟 Radius:** Adjust the radius of the particles using the slider. Tweak it to see how the particles interact at different sizes!
- **💫 Particle Count:** Use the slider to control the number of particles. The magic happens when you release the slider! (Range: 10 to 1000 particles)
- **🎨 Types Of Color:** Change the variety of particle colors. Slide, release, and watch the burst of colors! (Range: 2 to 8 colors)
- **🔄 Refresh:** Hit this to refresh the simulation with your current settings.
- **🔁 Wrap Particles To Viewport:** Toggle this to see if particles bounce back or loop around the edges of the screen!

### 📏 Distance Controls
- **🔍 Show MinDist Control:** Click to expand and set the minimum distance for each particle type/color. Perfect for fine-tuning interactions!
- **↔️ Same Min Dist:** Use this slider to apply the same minimum distance across all particle types/colors. (Range: 1 to 30)
- **🔍 Show MaxDist Control:** Click to expand and set the maximum distance for each particle type/color. Make particles more social or distant!
- **↔️ Same Max Dist:** Use this slider to apply the same maximum distance across all particle types/colors. (Range: 150 to 300)

### 🎛️ Focus Control Settings
- **🔀 Random Forces:** Shuffle the forces! Get a fresh set of interactions between particles with a click.
- **🔄 Reset Forces:** Reset all forces to zero—perfect for a clean slate.
- **🔽 Minimise Force:** Feeling minimal? Set all forces to -1.
- **🔼 Maximise Force:** Go all out by setting all forces to 1.
- **🎯 Default Force:** Use this to revert to predefined force values.
- **💾 Save Forces to File:** Save your current force setup to `forces.txt`—perfect for sharing or reloading later.
- **🎚️ Sliders:** Manually tweak the forces for each particle type/color pair. Get your hands dirty with the details!

### 📏 Minimum Distance Control (If Enabled)
- **🔀 Random Min Dist:** Randomize minimum distances—let the particles decide their own space!
- **🔽 Minimise Dist:** Set all minimum distances to the tightest value of 1.
- **🔼 Maximise Dist:** Spread them out by setting the minimum distances to 20.
- **🎯 Default Dist:** Go back to predefined distances with a click.
- **💾 Save Dist to File:** Save your min distance setup to `minDist.txt`.
- **🎚️ Sliders:** Manually adjust minimum distances for each particle type/color. (Range: 1 to 30)

### 📏 Maximum Distance Control (If Enabled)
- **🔀 Random Max Dist:** Randomize maximum distances—give your particles some breathing room!
- **🔽 Minimise Dist:** Tighten the space by setting all maximum distances to 150.
- **🔼 Maximise Dist:** Set maximum distances to 300, for a spacious simulation.
- **🎯 Default Dist:** Revert to default maximum distances.
- **💾 Save Dist to File:** Save your max distance setup to `maxDist.txt`.
- **🎚️ Sliders:** Manually adjust maximum distances for each particle type/color. (Range: 150 to 300)

### 🕹️ Navigation Controls
- **🔍 Zooming:** Use the mouse wheel to zoom in and out. Zoom in for details, zoom out for the big picture!
- **🖱️ Panning:** Click and hold the middle mouse button to pan the view. Explore different parts of the simulation!
- **🔄 Reset Zoom:** Press the `z` key to snap back to the default zoom level.
- **🔄 Reset Panning:** Press the `m` key to reset the panning to the default center view.

### 🖼️ Window Resizing
*You bet I’m proud of this feature!*
- **🪟 Main Window:** Drag the edges or corners of the main simulation window to resize it to your liking. Make it your own!
- **📐 Control Window:** The control window width is also adjustable. Customize your workspace for the ultimate simulation experience!
