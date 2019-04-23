public void lecture(){
  
  String nom=JOptionPane.showInputDialog("nom du fichier de chargement : (pas fini)");
  //if (nom == "")
  if(nom != null && nom.length() == 0)
    nom = "save";
   

 //le niveau est lu et enregistré dans String "lines"
  String lines[] = loadStrings("data/save/"+nom+".txt");
   
  

  int[] data;

  println("niveau de " + lines.length + "x"+ lines.length +" cases \n" );
  int yi=0,i=0;
  
    //data à tt le tableau pret
    data = int(split(lines[i], ' '));
    
   
    for (int xi=0; xi<nb_bits; xi++) {
      
      print(data[xi]+",");
       tab[xi][yi]=data[xi];
      }
       yi++;
      println();
  //}
}

/*
ça peut etre sympa de coder en binaire l'information des cases:
genre 0000 0001 c'est une plaine et 0000 0101 c'est un mage sur un land.

*/

/*
PROTOCOLE :
tailleX tailleY\n
data data data...




*/