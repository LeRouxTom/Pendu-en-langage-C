#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_MAX 1000


//===Base===
int NomJoueur();
char nomjoueur[255];
int DemandeLettre();
int viderBuffer();
char lettre;
int Win();
int taille;
char LettreDuJoueur;
int tentatives = 0;

//===Affichage===
int AffichagePendu();
int AffichageTab_tiret();
int InitTab_tiret();
char tiret[30];
int Nbrtirets;
int nombretirets();

//===Stockage lettre===
int IndiceTabStockage = 0;
char stockage_lettres_utilises[255];

//===Verification dans alphabet et mot===
char alphabet[26] = {"abcdefghijklmnopqrstuvwxyz"};
char mot[255];
int TailleMot();
int VerificationAlphabet();
int VerificationMot();
int LettreUtiliseeFaux();
int LettreUtiliseeBon();

//===Fichier et bonus===
int lecture_fichier_score();
int trie_classement();
int compteur_ligne_fichier = 0;
int ecritureFich();
int ecriture_top();
int fichier();
char stockageMotFich[1000][30];
int compteurmot = 0;
int choixdumot();


struct Classement_top{ //structure k le top 10 qui permet de trier les joueurs selon leur nombres de tentatives
	int scores_top;
	char pseudo[255];
};

struct Classement_top tab_top[100];

int trie_classement();
int lecture_fichier_score();

int main(){
	NomJoueur();
	srand(time(NULL));  //initialise le random avec time qui est un nombre aléatoire qui change chaque seconde
	fichier();
	choixdumot();
	TailleMot();
	InitTab_tiret();
	printf("il y a %d tirets dans le mot \n", Nbrtirets);
	while ((tentatives < 8) && (Nbrtirets > 0)){ //boucle qui vérifie si le mot n'a pas été trouvé et si le nombre de tentatives est inférieur à 8
		DemandeLettre();
		while((VerificationAlphabet() == 0) || (LettreDuJoueur== '\n')){ //on vérifie que la lettre utilisé est dans l'alphabet et que le lettre n'est pas un entré
			DemandeLettre(); 
		}	
		VerificationMot();
		printf("\nles lettres utilisées sont : %s\n", stockage_lettres_utilises); //affichage du tableau des lettres utilisés
		AffichagePendu();
	}
	trie_classement();
	lecture_fichier_score();
	Win();
	
}



int InitTab_tiret(){ //initialise un tableau composé de tirets
	int i;
	for (i = 0; i < taille; i++){
		tiret[i] = '_';
	}
}


int AffichageTab_tiret(){
	printf("\n%s\n", tiret); //affichage des tirets 
}


int NomJoueur(){
	int i = 0;
	printf("\nquel est ton nom? \n");
	char touche = getchar();
	while(touche != '\n'){ //si la touche est différente de ENTRER ça continue de prendre la touche appuyé cela permet de ne pas afficher seulement la première lettre du mot tapé
		nomjoueur[i] = touche;
		touche = getchar(); // la touche prend la valeur de getchar
		i++;
	}
	nomjoueur[i] = '\0';
	printf("\nton nom est : %s\n", nomjoueur);
}


int DemandeLettre(){ //probleme lorsque je met 2 fois des chiffres a la place des lettres
	printf("\ndonne une lettre : \n");
	LettreDuJoueur = getchar(); // la variable caractere prend la valeur de getchar
	printf("\ntu a choisi : %c\n", LettreDuJoueur);
	viderBuffer(); // on vide getchar pour ne pas comptabiliser le ENTRER
}

	
int VerificationAlphabet(){ //vérification de si la lettre se trouve dans l'alphabet
	int i;
	int conditionfonct;
	conditionfonct = 0;
	i = 0;
	while((conditionfonct == 0) && (i < 26)){ // si le i est inférieur a 26 (l'alphabet) et que conditionfonct est = 0 ça parcours la chaine alphabet pour dire si oui ou non c'est dedans 
		if ((alphabet[i] == LettreDuJoueur)){	
			conditionfonct = 1; // si y a la lettre dans l'alphabet ça met conditionfonct à 1 (booléen)
			}	
			i++;
		}
	if (conditionfonct == 1){ 
		printf("\nla lettre est dans l'alphabet =)\n");
	}
	else{
		printf("\nla lettre est pas dans l'alphabet ='[ \n");
	}
	return conditionfonct; //retourne la valeur de la variable condition et quitte la fonction. Cette valeur est utilisé dans le main.
}


int VerificationMot(){
	int i;
	int condition;
	i = 0;
	condition = 0;
	while (i<= taille){ // si les tentatives sont inférieur à 8 et que la le i est inférieur à la taille du mot on rentre dans la boucle
		if (mot[i] == LettreDuJoueur){ // dit la lettre est comprise dans le mot 
			tiret[i] = mot[i]; // on remplace le tiret par la lettre
			condition = 1; // on passe la condition à 1
		} 
		i++;
	}
	if (condition == 1){
		LettreUtiliseeBon(); // appelle de la fonction permettant de vérifier si la lettre a déjà été utilisé ou non si la lettre est dans le mot
	}
	else{
		LettreUtiliseeFaux(); // appelle de la fonction permettant de vérifier si la lettre a déjà été utilisé ou non si la lettre n'est pas dans le mot
	}
	AffichageTab_tiret();
}


int LettreUtiliseeFaux(){
	int verification_faux;
	verification_faux = 0;
	int i;
	i = 0;
	while(i <= 255){ // on parcourt tout le tableau de stockage des lettres
		if(stockage_lettres_utilises[i] == LettreDuJoueur){ // on vérifie si le caractere est dans le mot
			verification_faux = 1;  // si oui on passe la variable à 1
		}
		i++;
	}
	if (verification_faux == 1){
		printf("\ntu a déjà utilisé cette lettre mais tu ne perd pas de tentatives \n");
	}
	else{
		printf("\nla lettre est pas dans le mot \n");
		tentatives++; //on augmente les tentatives du joueurs car il a choisis un mauvais mot
		stockage_lettres_utilises[IndiceTabStockage] = LettreDuJoueur; // stockage du caractère dans le tableau qui représente toutes les lettres utilisées
		IndiceTabStockage++;
		stockage_lettres_utilises[IndiceTabStockage] = ' ';
		IndiceTabStockage++; //on augmente l'indice afin que le porchain caractère ne soit pas placé au même endroit

	}
}


int LettreUtiliseeBon(){
	int verification_bon;
	int i;
	verification_bon = 0;
	i = 0;
	while (i <= 255){ // on parcourt tout le tableau de stockage des lettres
		if (stockage_lettres_utilises[i] == LettreDuJoueur){ // on vérifie si le caractere est dans le mot
			verification_bon = 1; // si oui on passe la variable à 1
		}
		i++;
	}
	if (verification_bon == 1){
		printf ("\ntu a déjà utilisé cette lettre \n");
	}
	else{
		printf("\nla lettre est dans le mot \n");
		nombretirets(); // on appelle la fonction qui affiche les tirets pour voir ou à été placé la lettre
		stockage_lettres_utilises[IndiceTabStockage] = LettreDuJoueur; // stockage du caractere dans le tableau stockage
		IndiceTabStockage++;
		stockage_lettres_utilises[IndiceTabStockage] = ' ';
		IndiceTabStockage++; //on augmente l'indice afin que le porchain caractère ne soit pas placé au même endroit
		
	}
}


int AffichagePendu(){ //affichage pendu selon le nombre de tentatives 
	if (tentatives == 1){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
	}
	else if (tentatives == 2){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("  |          \n");
		printf("  |       	 \n");		
		printf("  |          \n");
		printf("  |          \n");
		printf("  |          \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
	}
	else if (tentatives == 3){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("   ______    \n");
		printf("  |          \n");
		printf("  |       	 \n");		
		printf("  |          \n");
		printf("  |          \n");
		printf("  |          \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
	}
	else if (tentatives == 4){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("   ______    \n");
		printf("  |      |   \n");
		printf("  |       	 \n");		
		printf("  |          \n");
		printf("  |          \n");
		printf("  |          \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n");
	}
	else if (tentatives == 5){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("   ______    \n");
		printf("  |      |   \n");
		printf("  |      0	 \n");		
		printf("  |          \n");
		printf("  |          \n");
		printf("  |          \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
	}
	else if (tentatives == 6){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("   ______    \n");
		printf("  |      |   \n");
		printf("  |      0	 \n");		
		printf("  |     /|\\ \n");
		printf("  |          \n");
		printf("  |          \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
	}
	else if (tentatives == 7){
		printf("\ntu es à %d tentatives\n", tentatives);
		printf("\n");
		printf("   ______   \n");
		printf("  |      |   \n");
		printf("  |      0	 \n");		
		printf("  |     /|\\ \n");
		printf("  |      |   \n");
		printf("  |          \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
	}
	else if (tentatives == 8){
		printf ("\n\nperdu !\n\n");
		printf("\n");
		printf("   _____    \n");
		printf("  |     |   \n");
		printf("  |     o 	 \n");		
		printf("  |    /|\\ \n");
		printf("  |     |   \n");
		printf("  |    / \\ \n");
		printf(" _|_         \n");
		printf("|   |______  \n"); 
		printf("|          | \n"); 
		printf("|__________| \n"); 
		printf("\nle mot était : %s\n", mot);
		ecritureFich();
	}		
}


int viderBuffer(){ //on vide le getchar
    int c=0; // initialisation de c à 0
    while (c != '\n' && c != EOF) // tant que c différent de retour à la ligne et fin du fichier c prend la valeur de getchar
        c=getchar();
}


int Win(){
	if(Nbrtirets == 0){ // on a crée une variable fin du jeu qu'on met à 0 si elle est à 0 et que le nombre de tiret est égale à 0. Cela veut dire qu'on à gagné on passe alors le finjeu à 1
		printf("\nTu a gagné ! \n");
		ecritureFich();
	}
}


int nombretirets(){
	int i;
	i = 0;
	while (i <= taille){ // si  i est inférieur à la taille du mot on rentre dans la boucle
		if (mot[i] == LettreDuJoueur){ // dit la lettre est comprise dans le mot 
			Nbrtirets--; //on baisse de 1 la variable nombre de tirets
		} 
		i++;
	}
}


int TailleMot(){ // permet de connaitre la taille de mon mot
	int i;
	i = 0;
	taille = 0;
	while (mot[i] != '\0'){ // tant que i n'arrive pas à la fin du mot
		i++;
		taille++; // on augmente la taille et i
	}
	Nbrtirets = taille; // le nombre de tirets est égales à la taille cela est utilisé pour la fonction win
}


int fichier()
{
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX]; // tableau de chaine de caractère qui permet de parcourir chaque mot
	fichier = fopen("words.txt", "r"); //ouvreture du fichier 'r' permet de lire dans le fichier 
	int i = 0;

	
	while (fgets(chaine, TAILLE_MAX, fichier) != NULL){ //fgets = lire une ligne
		while (chaine[i] != '\n'){ // on vérifie que l'indice n'est pas égale à entré ou caractère nul
			stockageMotFich[compteurmot][i] = chaine[i]; // on stocke la valeur de chaine de [i] dans le tableau fich
			i++;
		}
		stockageMotFich[compteurmot][i] = '\0'; // on met un caractère nulà la fin du tableau pour savoir ou il se termine
		compteurmot++; //permet de savoir le nombre de ligne du fichier
		i = 0; //on remet l'indice à 0 pour recommencer les prochains mot à l'indice 0
		
	}
	fclose(fichier); //fermeture du fichier
}


int choixdumot() {
	int ligne_rng = rand() % (compteurmot); // on fait le randome du nombre de ligne (compteurmot)
	int j = 0;
	char emplacementTab = stockageMotFich[ligne_rng][j]; // on initialise c au premier caractère du mot de la liogne random
	while( emplacementTab != '\0'){
		mot[j] = emplacementTab; // on le stocke dans le tableau mot qui sera par la suite le mot à deviner
		j++;
		emplacementTab = stockageMotFich[ligne_rng][j]; //on remet c égale au tableau à chaque fois qu'on augmente l'indice pour permettre de parcourir tout le mot
	}
	printf("\n");
	mot[j] = '\0'; // on met un caractère nul à chaque fin de mot pour savoir ou le mot se termine
}


int ecritureFich()
{
	FILE * fichier = NULL; 
	
	fichier = fopen ("classement_top_10", "a+"); //ouvre le fichier a+ permet décrire à la suite de ce qui est déjà dans le fichier 
	
	if(fichier != NULL) // si le fichier est différents de pas de valeur c'est à dire qu'il peut s'ouvrir
	{	
		fprintf(fichier,"%s|%d\n", nomjoueur, tentatives);	//affiche le pseudo et son score
				
	}
	fclose(fichier); //ferme le fichier
}



