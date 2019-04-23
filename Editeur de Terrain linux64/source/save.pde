void sauvegarde(){
  
  String [] list;
        list = new String[1];
        String nom=JOptionPane.showInputDialog("nom du fichier de sauvegarde"); 
        if(nom != null && nom.length() == 0)
          nom = "save";
        //screenshot
        save("data/save/"+nom+".png");
        
        /*la premiere ligne va etre géré appart*/
        
        list[0]= 0+" "+0+" "+tab[0][0]+" ";
        for(int i=1; i<nb_bits; i++){
          list[0]= list[0]+i+" "+0+" "+tab[i][0]+" ";
        }
        
        for (int j = 1 ; j<nb_bits ; j++){
          for(int i=0; i<nb_bits; i++){
            list[0]= list[0]+i+" "+j+" "+tab[i][j]+" ";
          }
        }
        //string to file
        saveStrings ("data/save/"+nom+".txt", list);
        
}