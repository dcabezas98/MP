#ifndef _IMAGEN_H_
#define _IMAGEN_H_

#include "byte.h"

/**
@brief Una imagen en blanco y negro. Cada píxel es un Byte
*/
class Imagen{
private: 
   Byte ** datos;///< datos de la imagen
   int nfilas; 			///< número de filas de la imagen
   int ncolumnas;		///< número de columnsa de la imagen
public:

   Imagen(); 
   
   Imagen(int filas, int columnas);
   
   Imagen (const Imagen &imagen1);
      
   Imagen& operator=(const Imagen &imagen1);

   ~Imagen();

   void crear(int filas, int columnas);
   
   int filas() const; 

   int columnas() const; 
   
   void set(int y, int x, Byte v); 

   Byte get(int y, int x) const; 
   
   void setPos(int i, Byte v); 
   
   Byte getPos(int i) const;

   bool leerImagen(const char nombreFichero[]);
   
   bool escribirImagen(const char nombreFichero[], bool esBinario) const; 
   
///////////////////////////////////////////////////////////////////////////////////
   Imagen plano (int k) const;
   
   bool aArteASCII(const char grises[], char arteASCII[], int maxlong) const;
///////////////////////////////////////////////////////////////////////////////////
};
#endif
