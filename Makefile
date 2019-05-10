all:
	g++ Main.cpp -o Ray-tracer-2D.exe -DSFML_STATIC -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype