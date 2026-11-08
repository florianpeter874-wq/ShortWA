# ShortWA (ShortWinAPI) 🚀

A lightweight, high-performance, and completely **portable single-header ecosystem** written in pure C to escape the complexity of Microsoft WinAPI and Direct3D 11.

Tired of writing half a million lines of boilerplate code just to open a native window and setup graphics? **Shortwa reduces it to a single line.**

---

## Key Features 🌟

- **Single-Header Architecture:** No complex installation. Just drop `shortwalib.h` into your project, and you are ready to go.
- **Zero Boilerplate:** Abstracts away all tedious Windows handle management (`HWND`, `HINSTANCE`) into a clean, modern interface.
- **Direct3D 11 Ready:** Built from the ground up to pair perfectly with modern, hardware-accelerated rendering loops.
- **Shortwa Math Ecosystem:** Comes bundled with `shortwamath.h`, an ultra-fast, pure C 3D game math library tailored for matrix transformations and vector operations.

---

## Current Roadmap 🗺️

1. 🪟 **Windows (Active Development):** Native WinAPI window management and Direct3D 11 integration.
2. 🐧 **Linux (Planned):** Native X11 / Xlib window context.
3. 🍏 **macOS (Planned):** Cocoa Objective-C runtime bridge.

---

## Getting Started (Windows) 💻

Because Shortwa is a **header-only library**, using it is incredibly simple. Define the implementation macro in *exactly one* C file before including the header.

### Quick Example: Opening a Windows Window
### Use it, not WinAPI, is shorter than

```c
#include "shortwalib.h"

int main() {
    // Just a single line to open a fully functional Windows window!
    ShortwaWindow win = Shortwa_CreateWindow(800, 600, "Shortwa Powered Engine");

    while (win.is_running) {
        Shortwa_ProcessEvents(&win);
        
        // Your game logic / Direct3D 11 rendering goes here
    }

    Shortwa_CloseWindow(&win);
    return 0;
}
```

---

## Licensing & Business Model 💼

Shortwa is developed under a **Dual-Licensing Model**:
- **Community License:** Completely free for open-source projects, students, and hobbyists.
- **Commercial License:** Required for commercial closed-source software and studios generating revenue. Contact the author for commercial licensing tiers.

---

*Developed with passion by the **Netfloor Software Corporation**.*
