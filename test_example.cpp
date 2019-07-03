#include "detector.hh"
//#include "particle_gun.hh"
#include "G4RunManager.hh"
//#include "QBBC.hh"
#include "physicsList.hh"
//#include "Randomize.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
//#include "G4UIterminal.hh"
//#include "G4MTRunManager.hh"
//#include "G4PhysListFactory.hh"
#include "N01PrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{
	G4UIExecutive* ui=0;
	if(argc==1){
		ui=new G4UIExecutive(argc,argv);
	}
	   
	G4RunManager* runManager= new G4RunManager;
	//runManager->SetNumberOfThreads(1);

	//detector construction
	DetectorGeom* detector=new DetectorGeom();
	runManager->SetUserInitialization(detector);
	
	//physics initialization && physics list 
	//G4VModularPhysicsList* physicsList=new QBBC;
	// G4PhysListFactory factory;
	// G4VModularPhysicsList* physList=factory.ReferencePhysList();
	G4VUserPhysicsList* physics = new PhysicsList;
	runManager->SetUserInitialization(physics);
	
	//particle source initialization

	G4VUserPrimaryGeneratorAction* myAction=new N01PrimaryGeneratorAction;
	runManager->SetUserAction(myAction);
	
	
	
	// visualization manager
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
	G4UImanager* UImanager= G4UImanager::GetUIpointer();

	if(!ui){
		G4String command="/control/execute ";
		G4String fileName=argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else {
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}

	delete runManager;
	return 0;



// 		G4UImanager* UImanager = G4UImanager::GetUIpointer();
// 		G4UIExecutive* ui = 0;
// 	if ( ! ui ) { 
//     // batch mode
//     G4String command = "/control/execute ";
//     G4String fileName = argv[1];
//     UImanager->ApplyCommand(command+fileName);
//   }



	//~ if(argc==1)
	//~ {
		//~ G4UIsession * session = new G4UIterminal;
		//~ UI->ApplyCommand("/control/execute prerun.g4mac");
		//~ session->SessionStart();
		//~ delete session;
	//~ }
	//~ else
	//~ {
		//~ G4String command = "/control/execute ";
		//~ G4String fileName=argv[1];
		//~ UI->ApplyCommand(command+fileName);
	//~ }
	//~ delete visManager;
	
	// runManager->Initialize();
	// G4UImanager* UI = G4UImanager::GetUIpointer();
	// UI->ApplyCommand("/run/verbose 1");
	// UI->ApplyCommand("/event/verbose 1");
	// UI->ApplyCommand("/tracking/verbose 1");
	
	// runManager->BeamOn(30);
	// delete runManager;
	// return 0;
	


}
