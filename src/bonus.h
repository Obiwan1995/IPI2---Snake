/**
 * @file bonus.h
 * @author Les Mixtes
 * @date 27/04/2016
 * @brief Header du fichier bonus.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion des bonus
 */

#ifndef _bonus_h_
#define _bonus_h_

/** Type du bonus : affecte soit la vitesse, soit la taille du serpent, soit l'emplacement de la tête et de la queue */
typedef enum Type {increase_speed, decrease_speed, increase_size, decrease_size, reverse} Type;

/** Effet du bonus : pour soi ou pour les autres */
typedef enum Effect {self, others} Effect;

/** Structure d'un bonus :
- Son type
- Son effet
- Le point où il est situé */
typedef struct {
	Type type;
	Effect effect;
	Point point;
} Bonus;

#endif