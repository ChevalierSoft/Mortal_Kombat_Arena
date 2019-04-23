void agrandi(){
  taille+=2;
  //background(255);
  for (int i=0; i < nb_sprites ; i++){
    sprite[i]=loadImage("ca"+i+".png");
    sprite[i].resize(0, taille);
  }
}

void raptici(){
  if (taille > 2) { taille-=2; /*background(0);*/ }
  for (int i=0; i < nb_sprites ; i++){
    sprite[i]=loadImage("ca"+i+".png");
    sprite[i].resize(0, taille);
  }
}

void resize(int w, int h){
 size(w,h);
 frame.setSize(w,h);
 
}