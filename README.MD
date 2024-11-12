# Zodiac Calculator V2.0

This repository contains the source code for the project **Zodiac Calculator V2.0**. This project was submitted as homework during my third year at [I.T.I.S. Magistri Cumacini](https://www.magistricumacini.edu.it/) to my I.T. teacher.

## 🔰 Badges

![GitHub Repo stars](https://img.shields.io/github/stars/0tia0/Zodiac-Calculator-V2.0?style=social) ![GitHub forks](https://img.shields.io/github/forks/0tia0/Zodiac-Calculator-V2.0?style=social)  

![GitHub issues](https://img.shields.io/github/issues/0tia0/Zodiac-Calculator-V2.0) ![GitHub pull requests](https://img.shields.io/github/issues-pr/0tia0/Zodiac-Calculator-V2.0) ![GitHub contributors](https://img.shields.io/github/contributors/0tia0/Zodiac-Calculator-V2.0)

## 👾 Tech Stack

**I.D.E.:** [VSCode](https://code.visualstudio.com/)

**Language:** *C++* with *graphics.h*

**Compiler:** [MinGW64](https://www.mingw-w64.org/) 
## 📋 Features

- Zodiac Sign **calculation** with **cusp** and **ascendant**
- Zodiac Sign display **Animation**
- Cool and modern **graphics** using and old **lib**

## ❓ FAQ

#### I'm waiting to receive any questions that should be placed here.

## 📸 Pictures

![Coming Soon](https://via.placeholder.com/468x300?text=Waiting+till+the+code+is+finished)


## 📥 Installation

You need to install the graphics.h library and its relative libs. All files can be found [here](https://github.com/SagarGaniga/Graphics-Library/) and should be placed in the respective folders: **.h** files in the compiler's **include** folder and **.a** files in the compiler's **lib** folder.

I personally recommend to use [MinGW64](https://www.mingw-w64.org/) as the compiler for this project, and place his **bin** folder inside the windows **System Enviroment Variables** 

## ⚙️ Deployment

After you have installed and configured the compiler you can run this command in the root folder of this project:
```sh
g++ main.cpp -o main.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lsfml-graphics -lsfml-window -lsfml-system
```
I reccomend to use the VSCode extension **code runner** to do all this stuff by just pressing a button. My personal configuration is:
```json
{
    "code-runner.runInTerminal": true, //true terminal //false output
    "code-runner.executorMap": {
            "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && .\\$fileNameWithoutExt",
            "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lsfml-graphics -lsfml-window -lsfml-system && .\\$fileNameWithoutExt ",
    },
}
```
All this should be placed inside the **settings.json** file from VSCode

## 📞 Support

For support, you can create an [issue](https://github.com/0tia0/Zodiac-Calculator-V2.0/issues) on this repository, as long as the project is supported

## 👨🏻‍💻 Authors

- Mattia Marelli: [@0tia0](https://www.github.com/0tia0)