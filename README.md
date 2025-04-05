# S6_Networking_Lab

## Basic Setup for Windows Users  
### WSL + VS Code Setup for Networking Labs  

This guide will help you set up your environment for networking labs using Linux headers and tools (like `<sys/socket.h>`, `<arpa/inet.h>`, etc.) with WSL and VS Code.

---

### Steps  

1. **Install WSL & Ubuntu**  
   Open PowerShell as Administrator and run:  
   ```bash
   wsl --install
   ```  
   This installs WSL 2 along with the default Ubuntu version. Restart your system when prompted.

2. **Verify Ubuntu Installation**  
   After rebooting, search for **Ubuntu** in the Start Menu and open it. Set your UNIX username and password.

3. **(Optional) Install a Specific Ubuntu Version**  
   If you want a specific version (e.g., Ubuntu 22.04), run:  
   ```bash
   wsl --install -d Ubuntu-22.04
   ```

4. **Install VS Code and WSL Extension**   
   - Open VS Code and install the **Remote - WSL** extension from the Extensions tab.


5. **Install Required Tools**  
   To install essential tools like `gedit`, `gcc`, and `build-essential`, run the following commands in the Ubuntu terminal:  
   ```bash
   sudo apt update && sudo apt upgrade -y
   sudo apt install gedit gcc build-essential
   ```  
   These tools are necessary for compiling and editing your networking programs.

---

### Running Server and Client Programs  
You can create two separate WSL terminals for running server and client programs. Here's an example setup:  
![image](https://github.com/user-attachments/assets/33f9f731-c780-4307-955f-0c06b872ca60)


---

## 🔗 Video Tutorial  

For a detailed walkthrough, check out this YouTube video (only the first half is necessary):  
🎥 [Install Windows Subsystem for Linux on Windows 11 - YouTube](https://www.youtube.com/watch?v=wz0QBNy9i7w&utm_source=chatgpt.com)

---

Now you're all set to run networking code with full Linux support in VS Code on your Windows system 🚀  

---

# Experiments  
