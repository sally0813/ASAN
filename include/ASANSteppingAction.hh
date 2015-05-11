#ifndef ASANSteppingAction_h
#define ASANSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class ASANEventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class ASANSteppingAction : public G4UserSteppingAction
{
  public:
    ASANSteppingAction(ASANEventAction* eventAction);
    virtual ~ASANSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    ASANEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
