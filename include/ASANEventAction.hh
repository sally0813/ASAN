#ifndef ASANEventAction_h
#define ASANEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class ASANEventAction : public G4UserEventAction
{
  public:
    ASANEventAction();
    virtual ~ASANEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    G4double  fEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
