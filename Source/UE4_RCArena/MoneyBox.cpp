
#include "MoneyBox.h"

AMoneyBox::AMoneyBox()
{
	// Set the mesh of the box
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BoxMeshObject(TEXT("/Game/Box/Mesh/SM_MoneyBox"));
	if (BoxMeshObject.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshObject.Object);
	}

	// Find the money class and store it for later
}

void AMoneyBox::BreakBox()
{

}
