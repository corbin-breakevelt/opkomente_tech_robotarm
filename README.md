# opkomende_tech_robotarm
# intro
Voor het vak opkomende technologieen was aan ons de vrije keuze gegeven om een project te maken met daarin een microcontroller verwerkt.
Om een klijne fantasie van ons alle twee te vervullen werd gekozen om een robotische arm te makken, meer bepaald een ...-assige arm en de daarbijhorende besturings mechanismen.
![Render van product](images/robotic_arm.png)
# CAD desing
Voor deze opdracht wouden we onze eigen arm ontwerpen. deze nam inspiratie op van in de industrie als de vele si-fi film die we gezien hadden.
een paar voorbelden van inspiratie bronnen: 

|![Render van product](images/refrence_1.png)  |![Render van product](images/refrence_2.png)  |
|--------|-----------|
|![Render van product](images/refrence_3.png)|

De 3D modelen werden uitgetekend in Siemens NX en zijn in bijlage beschikbaar in .prt formaat, .obj formaat als in .stl formaat.
de robot arm bestaat uit 5 moteren:
* 3 sevro motoren (aangeduid in het rood)
    * 1 in de klouw 
    * 1 in de bovenste scharnierpunt
    * 1 in het onderste scharnierpunt
* 2 stepper motoren ( aangeduid in het blouw)
    * 1 voor de rotatie van de klouw
    * 1 voor de rotatie van de arm 
<div style="display: flex; gap: 10px; align-items: center;">
  <img src="./images/exploded view.avi.gif" style="height: 500; width: auto;" alt="arm">

de code voor de arm :
[eind code](./code/robotarm_def_code_potmeter/robotarm_def_code_potmeter.ino)
