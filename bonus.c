int lecture_fichier_score()
{
	FILE * fichier = NULL;
	int score_joueur;
	int i = 0;
	char pseudo_joueur[255];
	char chaine_ligne[1000] = "";	
	fichier = fopen ("classement_top_10", "r");
	
	if (fichier != NULL)
	{
	while (fgets(chaine_ligne, 1000, fichier) != NULL){

		while (chaine_ligne[i] != '|'){ 
			pseudo_joueur[i] = chaine_ligne[i];
			i++;
			tab_top[compteur_ligne_fichier].pseudo[i] = chaine_ligne[i];
		
		}
		tab_top[compteur_ligne_fichier].pseudo[i] = '\0';
		pseudo_joueur[i] = '\0';
		
		while (chaine_ligne[i] != '\n'){
			score_joueur = chaine_ligne[i];
			i++;
		}
			
		i =0;	
		score_joueur = score_joueur - '0'; //passe le score de caractère à entier en utilisant la table ASCII
		printf("%s\n", pseudo_joueur);
		printf("%d\n", score_joueur);
		tab_top[compteur_ligne_fichier].scores_top = score_joueur;
		compteur_ligne_fichier++;	
		
		}
		
		printf("%d\n", compteur_ligne_fichier);
	}
	
	else{
		printf("le fichier n'a pas réussis à s'ouvrir\n");
	}
	
	fclose(fichier);
}


int trie_classement()
{
	
	int i,j;		
	int nombre_plus_petit;	
					
	for (i=0; i<compteur_ligne_fichier; i++){
		j =i;
		while ((j >0)&&(tab_top[j-1].scores_top > tab_top[j].scores_top)){
			nombre_plus_petit = tab_top[j].scores_top;
			tab_top[i].scores_top = tab_top[j-1].scores_top;
			tab_top[j-1].scores_top = nombre_plus_petit;
			j--;	
		}
	}	
	for(int i = 0; i < 10; i++) {
		printf("Place : %s %d\n", tab_top[i].pseudo, tab_top[i].scores_top);
	}					
}


int ecriture_top()
{
	FILE * fichier = NULL;
	
	fichier = fopen ("classement_top_10", "a+");
	int i=0;
	
	if(fichier != NULL)
	{	
	printf("salut");
	while ( i != '\0'){
		fprintf(fichier, "%s %d\n", tab_top[i].pseudo, tab_top[i].scores_top);	
		i++;
		}	
	}
	fclose(fichier);
}
