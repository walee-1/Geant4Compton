#include "G4RunManager.hh"
//#include "Randomize.hh"  //random number generator
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
//#include "G4UIterminal.hh" 
//UI terminal control
#include "G4MTRunManager.hh" //if we ever want to use multi threaded run manager



//#include "generalParticleSource.hh"
#include "PhysicsList.hh"

#include "detector.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"
//#include "particle_gun.hh" //if you want to use a particle gun directly 

#include <iostream>


int main(int argc, char** argv)
{
	if (std::rename("output.root","output_old.root")<0 || std::rename("output.txt","output_old.txt")<0|| std::rename("InputEn.txt","InputEn_old.txt")<0 
	|| std::rename("Secondary_output.txt","Secondary_output_old.txt")<0 || std::rename("output_All.txt","output_All_old.txt")<0){
		std::cout<<"OutputFiles: Output.root InputEn.txt Secondary_output.txt output_All.txt"<<G4endl;
	}
	else G4cout<<" Files renamed "<<G4endl<<G4endl;
	if(std::remove("output.txt")<0||std::remove("InputEn.txt")<0||std::remove("Secondary_output.txt")<0||std::remove("output_All.txt")<0){
		std::cout<<"A new output file will be written, woohoo!"<<std::endl;	
	}
	else std::cout<<"You dare run this program whilst an output.txt already exists?"<<std::endl<<
	"Now watch your kingdom engulf in flame as I lay waste to what"
	<< " you once recorded."<<std::endl;
	G4UIExecutive* ui=0;
	if(argc==1){
		ui=new G4UIExecutive(argc,argv);
	}
	//set up the run manager
	// G4MTRunManager* runManager= new G4MTRunManager;
	// runManager->SetNumberOfThreads(4);

	G4RunManager* runManager= new G4RunManager;
	// visualization manager
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	//detector construction
	DetectorGeom* detector=new DetectorGeom;
	runManager->SetUserInitialization(detector);
	
	//physics initialization && physics list 
	//G4VModularPhysicsList* PhysicsList=new QBBC;
	//G4PhysListFactory factory;
	//G4VModularPhysicsList* physList=factory.ReferencePhysList();

	runManager->SetUserInitialization(new PhysicsList);

	//runManager->SetUserInitialization(physList);
	//particle source initialization

	// //Primary Generator Action
	// G4VUserPrimaryGeneratorAction* myAction=new N01PrimaryGeneratorAction;
	// runManager->SetUserAction(myAction);
	
	runManager->SetUserInitialization(new ActionInitialization());

	//runManager->Initialize(); //If you want to use multiple physics list, for the love of all that is holy and pure and what you hold dear
								//do NOT initialize the run manager, instead do it in the freaking vis manager. If you do uncomment it, the
								//program will run the local physics list. You can of course change it to a different standard but then don't
								//put it in your vis.mac file. 
	
	
	G4UImanager* UImanager= G4UImanager::GetUIpointer();
	//if you send a command with the execution of the binary
	if(ui){
		
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	//if you just want to use vis.mac
	else {
		G4String command="/control/execute ";
		G4String fileName=argv[1];
		UImanager->ApplyCommand(command+fileName);

	}

	//free up memory
	//delete visManager;
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
