int[][] tab;
int cl=0, n, lvl;
byte act=0;
//import javax.swing.*;
import javax.swing.JOptionPane;

/*nombre de sprit de terrain*/
int nb_sprites = 6;
/*taille x et y #degeulase*/
int nb_bits = 10;
/*taille des sprites*/
int taille = 50;

PImage sprite[] = new PImage[nb_sprites];

void zero(int tab[][]){
 for (int xi=0; xi<nb_bits; xi++) {
    for (int yi=0; yi<nb_bits; yi++) {
      tab[xi][yi]=0;
    }
  } 
}

void setup() {

  //fullScreen();
  size(600, 600, P2D);
  surface.setResizable(true);
  background(0);

  //frameRate(60);
  
  for (int i=0; i < nb_sprites ; i++){
    sprite[i]=loadImage("ca"+i+".png");
    sprite[i].resize(0, taille);
  }
  
  tab=new int[nb_bits][nb_bits];
  zero(tab);
  /*for (int xi=0; xi<nb_bits; xi++) {
    for (int yi=0; yi<nb_bits; yi++) {
      tab[xi][yi]=0;
    }
  }*/
  
}

void draw() {
  background(0);
  for (int xi=0; xi<nb_bits; xi=xi+1) {
    for (int yi =0; yi<nb_bits; yi=yi+1) {

      n=tab[xi][yi];
      for(int i=0; i<nb_sprites; i++){
        if (n==i) {
          image(sprite[i] , xi*taille, yi*taille);
          break;
        }
      }
      
    }
  }
  
  inputs();
  ui();
}