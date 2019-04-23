void inputs(){
  
  /*  INPUTS*/
  if (keyPressed == true){
     if (key == '+') {
       agrandi();
     }
     else if (key == '-') {
       raptici();
     }
     else if (key == 's') {
        sauvegarde();
     }
     else if (key == 'l') {
        lecture();
     }
     else if (key == 'e') {
         zero(tab);
     }
  }
  
}

int detect( int t) {
  return t/taille;
}


void mousePressed() {
  int xi,yi;
  if ((mouseY<taille*nb_bits) && (mouseY>0) && (mouseX>0)  && (mouseX<taille*nb_bits)) {
    xi=(detect(mouseX));
    yi=(detect(mouseY));
    cl++;
    //tester xi et yi compris entre 0 et 9

    change(xi,yi);
  }

}

void change(int xi, int yi) {

  if (tab[xi][yi]<nb_sprites) {
    tab[xi][yi]++;
  } else {
    tab[xi][yi]=0;
  }
  
  
}