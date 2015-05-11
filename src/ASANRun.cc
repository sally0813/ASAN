#include "ASANRun.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ASANRun::ASANRun()
: G4Run(),
  fEdep(0.), 
  fEdep2(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ASANRun::~ASANRun()
{} 
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ASANRun::Merge(const G4Run* run)
{
  const ASANRun* localRun = static_cast<const ASANRun*>(run);
  fEdep  += localRun->fEdep;
  fEdep2 += localRun->fEdep2;

  G4Run::Merge(run); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ASANRun::AddEdep (G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


