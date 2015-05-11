
#ifndef ASANActionInitialization_h
#define ASANActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class ASANActionInitialization : public G4VUserActionInitialization
{
  public:
    ASANActionInitialization();
    virtual ~ASANActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
