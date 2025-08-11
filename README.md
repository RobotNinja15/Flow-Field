## Flow Field in C - Because C++ overwhelms me

**This is a Simple flow field visualizer written in C.** 


## Images:
<img width="1286" height="971" alt="11111image" src="https://github.com/user-attachments/assets/2f07e681-bc47-4fe6-9df1-19f805248cec" />
<img width="1278" height="963" alt="i1111mage" src="https://github.com/user-attachments/assets/11cb5de4-d096-49e5-93c2-7648fcb8b721" />
<img width="1274" height="965" alt="image111" src="https://github.com/user-attachments/assets/eb0e845c-7e74-4210-8f16-80fdf92e09b7" />
<img width="1290" height="962" alt="image11111" src="https://github.com/user-attachments/assets/166d04c6-1762-4e10-a235-0b9a09e59c34" />

The code is not the best to be honest, but I have made some effort to add comments to make everything clear.

I made use of the dos-like library/framework made by Mattias Gustavsson. 

If you want to compile this you will need the Tiny C compiler, which is bundled with the files:
```
tcc\tcc .\main.c dos.c
```

There are adjustable values in the program that you can change to get different patterns.
`#define NB `
`#define NOISE_SCALE`
`#define NOISE_ANGLE`
`float noiseSpeed`
## other

I made this because I couldn't find any "simple" C implementation of a flow field. All or most of the examples I could find were in C++ and that language overwhelms me, so I avoided even checking them out. 

Anyway enjoy.

Kenneth
