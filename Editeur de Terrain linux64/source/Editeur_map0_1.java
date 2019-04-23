import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import javax.swing.JOptionPane; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Editeur_map0_1 extends PApplet {

int[][] tab;
int cl=0, n, lvl;
byte act=0;
//import javax.swing.*;


/*nombre de sprit de terrain*/
int nb_sprites = 6;
/*taille x et y #degeulase*/
int nb_bits = 10;
/*taille des sprites*/
int taille = 50;

PImage sprite[] = new PImage[nb_sprites];

public void zero(int tab[][]){
 for (int xi=0; xi<nb_bits; xi++) {
    for (int yi=0; yi<nb_bits; yi++) {
      tab[xi][yi]=0;
    }
  } 
}

public void setup() {

  //fullScreen();
  
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

public void draw() {
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
public void ui(){
  fill(170,170,255);
  text("'e' : \u00e9craser",10, 15);
  text("'s' : sauvegarder",120, 15);
  text("'l' : ouvrir",250, 15);
  
  
}
public void inputs(){
  
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

public int detect( int t) {
  return t/taille;
}


public void mousePressed() {
  int xi,yi;
  if ((mouseY<taille*nb_bits) && (mouseY>0) && (mouseX>0)  && (mouseX<taille*nb_bits)) {
    xi=(detect(mouseX));
    yi=(detect(mouseY));
    cl++;
    //tester xi et yi compris entre 0 et 9

    change(xi,yi);
  }

}

public void change(int xi, int yi) {

  if (tab[xi][yi]<nb_sprites) {
    tab[xi][yi]++;
  } else {
    tab[xi][yi]=0;
  }
  
  
}
public void lecture(){
  
  String nom=JOptionPane.showInputDialog("nom du fichier de chargement : (pas fini)");
  //if (nom == "")
  if(nom != null && nom.length() == 0)
    nom = "save";
   

 //le niveau est lu et enregistr\u00e9 dans String "lines"
  String lines[] = loadStrings("data/save/"+nom+".txt");
   
  

  int[] data;

  println("niveau de " + lines.length + "x"+ lines.length +" cases \n" );
  int yi=0,i=0;
  
    //data \u00e0 tt le tableau pret
    data = PApplet.parseInt(split(lines[i], ' '));
    
   
    for (int xi=0; xi<nb_bits; xi++) {
      
      print(data[xi]+",");
       tab[xi][yi]=data[xi];
      }
       yi++;
      println();
  //}
}

/*
\u00e7a peut etre sympa de coder en binaire l'information des cases:
genre 0000 0001 c'est une plaine et 0000 0101 c'est un mage sur un land.

*/

/*
PROTOCOLE :
tailleX tailleY\n
data data data...




*/
public void agrandi(){
  taille+=2;
  //background(255);
  for (int i=0; i < nb_sprites ; i++){
    sprite[i]=loadImage("ca"+i+".png");
    sprite[i].resize(0, taille);
  }
}

public void raptici(){
  if (taille > 2) { taille-=2; /*background(0);*/ }
  for (int i=0; i < nb_sprites ; i++){
    sprite[i]=loadImage("ca"+i+".png");
    sprite[i].resize(0, taille);
  }
}

public void resize(int w, int h){
 size(w,h);
 frame.setSize(w,h);
 
}
public void sauvegarde(){
  
  String [] list;
        list = new String[1];
        String nom=JOptionPane.showInputDialog("nom du fichier de sauvegarde"); 
        if(nom != null && nom.length() == 0)
          nom = "save";
        //screenshot
        save("data/save/"+nom+".png");
        
        /*la premiere ligne va etre g\u00e9r\u00e9 appart*/
        
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
  public void settings() {  size(600, 600, P2D); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "Editeur_map0_1" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
