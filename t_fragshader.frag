#version 130

in vec3 fragmentColor ;
out vec3 color;

void main(){
   //color = vec3(0.18,0.58,0.18);
   if(fragmentColor == vec3(0.0,0.0,0.0)){
       color = vec3(1.0,0.5,1.0);
   }
   else{
        color = fragmentColor;
   }
}