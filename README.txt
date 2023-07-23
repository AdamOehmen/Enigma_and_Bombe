Enigma setup:

1: Right Click on Project and click on Properties 
2: Navigate to Configuration Properties -> Linker -> General -> Additional Library Directories 
3: Change this to your own Directory, should follow this format: 
C:\Users\your_username\source\repos\Enigma_and_Bombe\Enigma_and_Bombe 
4: Navigate to Configuration Properties -> C/C++ -> General -> Additional Include Directories 
5: Copy and paste the same directory 

Bombe setup: 

Right click Bombe project in Visual Studio and select Properties 

1: Under VC++ Directories 
	"Include Directories": [path to your \Enigma_and_Bombe\Enigma_and_Bombe;]$(VC_IncludePath);$(WindowsSDK_IncludePath); 
		-example: C:\Users\Ethan\Documents\WIT\23_Summer\AppliedProgConcepts\EnigmaBombe\Enigma_and_Bombe;$(VC_IncludePath);$(WindowsSDK_IncludePath); 

2: Under C/C++ 
    "Additional Include Directories": [path to your \Enigma_and_Bombe] 
		-example: C:\Users\Ethan\Documents\WIT\23_Summer\AppliedProgConcepts\EnigmaBombe\Enigma_and_Bombe 

3: Under Linker -> General 
    "Additional Library Directories": [path to your \Enigma_and_Bombe\x64\Debug];[path to your \Enigma_and_Bombe\] 
		-example: C:\Users\Ethan\Documents\WIT\23_Summer\AppliedProgConcepts\EnigmaBombe\Enigma_and_Bombe\x64\Debug;C:\Users\Ethan\Documents\WIT\23_Summer\AppliedProgConcepts\EnigmaBombe\Enigma_and_Bombe 

4: Under Linker -> Input 
	“Additional Dependencies”: Plugboard.obj;Reflector.obj;Rotor.obj;sqlite3.lib;%(AdditionalDependencies) 

Running Enigma:
Right click the Enigma_and_Bombe project in Visual Studio
Select Set as Startup Project
Hit the green Run button at the top

Running Bombe:
Right click the Bombe project in Visual Studio
Select Set as Startup Project
Hit the green Run button at the top