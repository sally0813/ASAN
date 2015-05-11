#include "ASANDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ASANDetectorConstruction::ASANDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ASANDetectorConstruction::~ASANDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ASANDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;
  
  // Envelope parameters
  G4double env_sizeXY = 100*cm, env_sizeZ = 100*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // World
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Shape 1
  std::vector<G4int> natoms;
  std::vector<G4String> elements;
  G4double density = 1.180*g/cm3;

  elements.push_back("C");     natoms.push_back(5);
  elements.push_back("H");     natoms.push_back(8);
  elements.push_back("O");     natoms.push_back(2);

  G4Material* shape1_mat = nist->ConstructNewMaterial("PMMA", elements, natoms, density);
  G4ThreeVector pos1 = G4ThreeVector(0, 0*cm, 0*cm);
       
  G4double s1innerRadiusOfTheTube = 0.5*cm;
  G4double s1outerRadiusOfTheTube = 8.*cm;
  G4double s1heightOfTheTube = 15.*cm;
  G4double s1startAngleOfTheTube = 0.*deg;
  G4double s1spanningAngleOfTheTube = 360.*deg;
 
  // Shape 2
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_GRAPHITE");
  G4ThreeVector pos2 = G4ThreeVector(0, 0*cm, 0*cm);
  // Cylinder
  G4double s2innerRadiusOfTheTube = 0.*cm;
  G4double s2outerRadiusOfTheTube = 0.4*cm;
  G4double s2heightOfTheTube = 10.*cm;
  G4double s2startAngleOfTheTube = 0.*deg;
  G4double s2spanningAngleOfTheTube = 360.*deg;

  // Shape 3
  G4Material* shape3_mat = nist->FindOrBuildMaterial("G4_C-552");
  G4ThreeVector pos3 = G4ThreeVector(0, 0*cm, 0*cm);
  // Cylinder
  G4double s3innerRadiusOfTheTube = 0.4*cm;
  G4double s3outerRadiusOfTheTube = 0.5*cm;
  G4double s3heightOfTheTube = 10.*cm;
  G4double s3startAngleOfTheTube = 0.*deg;
  G4double s3spanningAngleOfTheTube = 360.*deg;

  // Shape 4
  G4Material* shape4_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector pos4 = G4ThreeVector(0, 0*cm, 0*cm);
  // Cylinder
  G4double s4innerRadiusOfTheTube = 8*cm;
  G4double s4outerRadiusOfTheTube = 8.1*cm;
  G4double s4heightOfTheTube = 15.*cm;
  G4double s4startAngleOfTheTube = 0.*deg;
  G4double s4spanningAngleOfTheTube = 360.*deg;
 

  /// Create objects

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //
  //Shape 1
  //

  G4Tubs* solidShape1
    = new G4Tubs("Shape1",
                 s1innerRadiusOfTheTube, 
                 s1outerRadiusOfTheTube,
                 s1heightOfTheTube/2,
                 s1startAngleOfTheTube, 
                 s1spanningAngleOfTheTube);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  //     
  // Shape 2
  //

  G4Tubs* solidShape2
    = new G4Tubs("Shape2",
                 s2innerRadiusOfTheTube, 
                 s2outerRadiusOfTheTube,
                 s2heightOfTheTube/2,
                 s2startAngleOfTheTube, 
                 s2spanningAngleOfTheTube);

  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name

               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Shape 3
  //

  G4Tubs* solidShape3
    = new G4Tubs("Shape3",
                 s3innerRadiusOfTheTube, 
                 s3outerRadiusOfTheTube,
                 s3heightOfTheTube/2,
                 s3startAngleOfTheTube, 
                 s3spanningAngleOfTheTube);

  G4LogicalVolume* logicShape3 =                         
    new G4LogicalVolume(solidShape3,         //its solid
                        shape3_mat,          //its material
                        "Shape3");           //its name

               
  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicShape3,             //its logical volume
                    "Shape3",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



////

  //
  //Shape 4
  //

  G4Tubs* solidShape4
    = new G4Tubs("Shape4",
                 s4innerRadiusOfTheTube, 
                 s4outerRadiusOfTheTube,
                 s4heightOfTheTube/2,
                 s4startAngleOfTheTube, 
                 s4spanningAngleOfTheTube);
                      
  G4LogicalVolume* logicShape4 =                         
    new G4LogicalVolume(solidShape4,         //its solid
                        shape4_mat,          //its material
                        "Shape4");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

////
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
