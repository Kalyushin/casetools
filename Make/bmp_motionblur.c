#include "bmp.h"
#include "stdlib.h"
#include <stdio.h>
/*
 * /file
 * Размытие в движении 
*/

void improve(double *a, unsigned int w, unsigned h,bmp_image image);

/**
   \brief Функция реализующая фильтр размытия в движении
   \param image Структура с информацией о изображении
*/
void bmp_motionblur(bmp_image image)
{
    unsigned int i, j;

    /* Получаем линейные размеры изображения */
    unsigned int w = image.header.width;
    unsigned int h = image.header.height;    

    /* Создание расширенного изображения */
    double *a;
    a = (double*) malloc (sizeof (double) * h * w * 3);
    improve (a, w, h, image);
    /* Матрица умножения */
    int matrix[5][5] = { { 2, 1, 1, 0, 0},
			 { 1, 1, 2, 1, 0},
			 { 0, 0, 1, 1, 1},
			 { 0, 0, 0, 1, 2},
			 {0, 0, 0, 0, 1}};
    

    /* Для всех слоёв */
    for (int p = 0; p < 3; p++) {
	/* Для всех строк */
	for (i = 0; i < h; i++) {
	    /* Для каждого пикселя */
	    for(j = 0; j < w; j++) {
		double sum = 0;
		/* Умножаем на матрицу окр.элементы */
		for (int sm = -2; sm < 3; sm++) {
		    for (int lm = -2; lm < 3; lm++) {
			int y = i + sm;
			int x = j + lm;
			if (y < 0) y = 0;
		        if (x < 0) x = 0;
			if (y >= (int) h) y = (int) h - 1;
		        if (x >= (int) w) x = (int) w - 1;
			sum = sum + matrix[sm + 2][lm + 2] *
			    a[p * h * w + y * w  + x];
		    }
		}
		image.pixel_array[p * h * w + i * w + j] = sum / 16;            
		if (image.pixel_array[p * h * w + i * w + j] == 1 ) {
		    printf("%f \n" , image.pixel_array[p * h * w + i * w + j]);
		}
	    }
	}
    }
    free(a);
}

/**
* @brief Вспомогательная функция для создания расширенного изображения
* @param image Изначальное изображение класса bmp_image.
* @param w Ширина изначального изображения.
* @param h Высота изначального изображения.
* @param a  Ссылка на массив для пикселей нового изображения.
*/
void improve(double *a, unsigned int w, unsigned h, bmp_image image) {
    unsigned int s,l; /* Индексы */ 
    for (s = 0; s < h; s++) {
        for(l = 0; l < w; l++) {
            a [0 * h  * w + s * w  + l]
		=image.pixel_array[0 * h * w + s * w + l];
	    a [1 * h * w + s * w + l]
		=image.pixel_array[1 * h * w + s * w + l];
	    a [2 * h * w + s * w + l]
		=image.pixel_array[2 * h * w + s * w + l];
        }      
    }
}
/* #include "bmp.h"
#include "stdlib.h"

 // Размытие в движении 

void improve(double *a, unsigned int w, unsigned h,bmp_image image);

void bmp_motionblur(bmp_image image)
{
    unsigned int i, j;

    // Получаем линейные размеры изображения 
    unsigned int w = image.header.width;
    unsigned int h = image.header.height;

    // Создание расширенного изображения 
    double *a;
    a = (double*) malloc (sizeof (double) * (h + 4) * (w + 4) * 3);
    improve (a, w, h, image);
    // Матрица умножения 
    int matrix[5][5] = { { 2, 1, 1, 0, 0},
			 { 1, 1, 2, 1, 0},
			 { 0, 0, 1, 1, 1},
			 { 0, 0, 0, 1, 2},
			 {0, 0, 0, 0, 1}};
    

    // Для всех слоёв 
    for (int p = 0; p < 3; p++) {
        // Для всех строк 
	for (i = 2; i < h + 2; i++) {
	    // Для каждого пикселя 
	    for(j = 2; j < w + 2; j++) {
		double sum = 0;
		// Умножаем на матрицу окр.элементы 
		for (int sm = -2; sm < 3; sm++) {
		    for (int lm = -2; lm < 3; lm++) {
			sum = sum + matrix[sm + 2][lm + 2] *
			    a[p * (h + 4) * (w + 4) + (i + sm) * (w + 4) + (j + lm)];
		    }
		}
		image.pixel_array[p * h * w + (i - 2) * w + (j - 2)] = sum / 16;            
	    }
	}
    }
    free(a);
}

void improve(double *a, unsigned int w, unsigned h, bmp_image image) {
    unsigned int s,l; // Индексы 
    for (s = 2; s < h + 2; s++) {
        for(l = 2; l < w + 2; l++) {
            
            a [0 * (h + 4) * (w + 4) + s * (w + 4) + l]
		=image.pixel_array[0 * h * w + (s - 2) * w + (l - 2)];
	    a [1 * (h + 4) * (w + 4) + s * (w + 4) + l]
		=image.pixel_array[1 * h * w + (s - 2) * w + (l - 2)];
	    a [2 * (h + 4) * (w + 4) + s * (w + 4) + l]
		=image.pixel_array[2 * h * w + (s - 2) * w + (l - 2)];
        }
    }
    for (s = 0; s < 2; s++) {
        for(l = 2; l < w + 2; l++) {
            
            a [0 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [0 * (h + 4) * (w + 4) + 2 * (w + 4) + l];
	    a [1 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [1 * (h + 4) * (w + 4) + 2 * (w + 4) + l];
	    a [2 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [2 * (h + 4) * (w + 4) + 2 * (w + 4) + l];
        }
    }
    for (s = h + 2; s < h + 4; s++) {
        for(l = 2; l < w + 2; l++) {
            
            a [0 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [0 * (h + 4) * (w + 4) + (h + 1) * (w + 4) + l];
	    a [1 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [1 * (h + 4) * (w + 4) + (h + 1) * (w + 4) + l];
	    a [2 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [2 * (h + 4) * (w + 4) + (h + 1) * (w + 4) + l];
        }
    }
    for (s = 0; s < h + 4; s++) {
        for(l = 0; l < 2; l++) {
            
            a [0 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [0 * (h + 4) * (w + 4) + s * (w + 4) + 2];
	    a [1 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [1 * (h + 4) * (w + 4) + s * (w + 4) + 2];
	    a [2 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [2 * (h + 4) * (w + 4) + s * (w + 4) + 2];
        }
    }
    for (s = 0; s < h + 4; s++) {
        for(l = w + 2; l < w + 4; l++) {
            
            a [0 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [0 * (h + 4) * (w + 4) + s * (w + 4) + 2];
	    a [1 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [1 * (h + 4) * (w + 4) + s * (w + 4) + 2];
	    a [2 * (h + 4) * (w + 4) + s * (w + 4) + l]
		= a [2 * (h + 4) * (w + 4) + s * (w + 4) + 2];
        }
    }
} */
