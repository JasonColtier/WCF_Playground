// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WFCPlayground/TRACE.h"
#include "JcoGridSlot.h"
#include "JcoGrid.generated.h"

class AJcoGridSlot;
typedef TArray<TPair<AJcoGridSlot*,TEnumAsByte<Directions>>> Neighbours;

UCLASS()
class WFCPLAYGROUND_API AJcoGrid : public AActor
{
	GENERATED_BODY()
	
public:

	
	/**
	* \brief un solt contenu dans la Grid. Il contient les possibilités 
	*/
	UPROPERTY(EditAnywhere,Category = "WFC")
	TSubclassOf<AJcoGridSlot> gridSlot;


	/**
	 *	Taille de la grille
	 */
	UPROPERTY(EditAnywhere,Category = "WFC")
	int sizeX = 3;
	UPROPERTY(EditAnywhere,Category = "WFC")
	int sizeY = 3;
	UPROPERTY(EditAnywhere,Category = "WFC")
	int sizeZ = 3;

	/**
	* \brief La grille instantiée
	*/
	UPROPERTY(EditAnywhere,Category = "WFC")
	TArray<AJcoGridSlot*> grid;
	
	// Sets default values for this actor's properties
	AJcoGrid();

	/**
     * \brief Initialise la grille en la remplissant de slots
     */
    void InitGrid();

	/**
	 * \brief Initialise tous les slots avec les possibilités
	 */
	void InitAllPossibilities();
	
	/**
     * \brief Print tous les éléments de la grille
     */
    void Print();

	void PrintNeighbours(Neighbours neighbours);
	
	/**
	 * \return Retourne un slot de la grille aux coordonnées voulues
	 */
	AJcoGridSlot* get(unsigned x, unsigned y, unsigned z);

	/**
	 * \return Return le slot avec le plus petit nombre de possibilités
	 * si égalités c'est random
	 */
	AJcoGridSlot* getMinEnthropySlot();

	
	/**
	 * \return Retourne les voisins d'une cellule
	 */
	void getNeibourghs(AJcoGridSlot* collapsedSlot, Neighbours& neighbours);



	bool isCollapsed();
	
	//todo collapse !
	// get le min enthropy
	// choisi random une possibilité
	// récupère tous les voisins
	// update leurs possibilités en fonction des contraintes
	// repeat

	//exemple : GC GC   GC GC  >C  C   
	//			GC GC  >G  G    G  G

	//exemple : GC GC   C  C
	//			GC GC  >C  C

	void Collapse();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
