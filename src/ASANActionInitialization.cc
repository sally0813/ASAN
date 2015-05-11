#include "ASANActionInitialization.hh"
#include "ASANPrimaryGeneratorAction.hh"
#include "ASANRunAction.hh"
#include "ASANEventAction.hh"
#include "ASANSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ASANActionInitialization::ASANActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ASANActionInitialization::~ASANActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ASANActionInitialization::BuildForMaster() const
{
  SetUserAction(new ASANRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ASANActionInitialization::Build() const
{
  SetUserAction(new ASANPrimaryGeneratorAction);
  SetUserAction(new ASANRunAction);
  
  ASANEventAction* eventAction = new ASANEventAction;
  SetUserAction(eventAction);
  
  SetUserAction(new ASANSteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
