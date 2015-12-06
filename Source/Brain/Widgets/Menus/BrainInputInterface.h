#pragma once

#include "BrainInputInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBrainInputInterface : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class IBrainInputInterface
{   
	GENERATED_IINTERFACE_BODY()

public:
	virtual FName GetInputName() = 0;
	virtual FText GetDisplayValue() = 0;
};