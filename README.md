# Tuinisian-Dama

a C++/OpenGL multilayer board game I used to play it in my childhood it's a strategy game which involve sideways movement of pieces and mandatory captures by jumping over opponent pieces.\
i made it using my [Game engine](https://github.com/ihebrachdi/Game-Engine).\
For the multiplayer Network I implemented a Client-Server Game Architecture using TCP/IP Protocol for data transfer 

---

## Running

### To run server:
you need first to built and run the server you will find it in the SERVER folder.
enter a valide port number exp:36000.\ 
The server will wait for a two clients to connects and once they do each one will receive it pieces color and as usual the white pieces start first.

![server]{screenshot\server.PNG}

---

### To run client:
after you build and run it you need to enter local or public IP address and the Port number it will be provide it by the server each time you run it\

![server]{screenshot\client connect.PNG}

\
---

## Screenshots

![server]{screenshot\tunisian dama.PNG}

\

![server]{screenshot\tunisian dama capture.PNG}

---

## Dependencies

GLFW\
GLEW\
SFML_Network
