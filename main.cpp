#include <iostream> // Implémentation du print et de l'accès aux fichiers.
#include <math.h>   // Implémentation des fonctions trigonométriques.

/**
 * Longueur du cercle constant par définition.
 * Exprimée en cm.
 */
static const double CIRCLE_WIDTH { 4 };

/**
 * Puissance de la lampe en Watt écrite sur le socle de la lampe.
 * Exprimée en W.
 */
static const double LIGHT_POWER { 4.5 };

/**
 * Nombre de valeur a enregistrée.
 */
static const unsigned short int NB_VALUE { 1000 };

/**
 * Valeur qui incrémente l'angle.
 * Nous voulons 1,000 valeurs !
 */
static const double INCREMENT_VALUE { (double) 90 / NB_VALUE };

/**
 * Constante de PI.
 */
static const double PI { 3.14159265 };

/**
 * Calcul de la hauteur du cercle.
 * Exprimée en cm.
 * @param alpha a double argument.
 */
inline double calcH(double alpha)
{
  return CIRCLE_WIDTH / cos(alpha * PI / 180.0);
}

/**
 * Calcul la surface de l'ellipse obtenue.
 * Exprimée en cm carré.
 * @param height a double argument.
 */
inline double calcS(double height)
{
  return PI * CIRCLE_WIDTH * height;
}

/**
 * Calcul de la puissance par unité de surface
 * Exprimée en W par centimètre puissance -2.
 * @param surface a double argument.
 */
inline double calcPUS(double surface)
{
  return LIGHT_POWER / surface;
}

int main() 
{
  FILE *pFile { fopen ("result.csv", "w") }; // Création du fichier et ouverture
  
  if(pFile != NULL)
    fputs("Angle,Longueur,Hauteur,Surface,P.U.S\n", pFile); // Ecriture des en-têtes CSV.
  
  double angle { 0 };
  
  for(unsigned short int i { 0 }; i != NB_VALUE; i++)
  {
    int const nextValue { i + 1 };

    double const height { calcH(angle) };
    double const surface { calcS(height) };
    double const pus { calcPUS(surface) };

    printf("Angle=%f Longueur=%f Hauteur=%f Surface=%f P.U.S=%f\n",
            angle,   CIRCLE_WIDTH, height, surface, pus);

    /** 
     * Préparation de la ligne à écrire.
     * - Convertion de variable typée double (décimaux) en chaîne de caractères.
     * - Ajout via une expression ternaire le saut de ligne ou non. 
     */
    std::string const line 
    {  
      std::to_string(angle)             + ',' // Angle
    + std::to_string(CIRCLE_WIDTH)      + ',' // Longueur
    + std::to_string(height)            + ',' // Hauteur
    + std::to_string(surface)           + ',' // Surface
    + std::to_string(pus)               + (nextValue != NB_VALUE ? "\n" : "") // Puissance par Unité de Surface (P.U.S)
    };

    if(pFile != NULL)
      fputs(line.data(), pFile); // Ecriture.
    
    angle += INCREMENT_VALUE;
  }

  if(pFile != NULL)
    fclose(pFile); // Fermeture du fichier en enregistrant les données écrites.
}
