#version 130

in vec3 fragmentColor ;
out vec3 color;

vec3 getColor(vec3 colorSample){
    vec3 tempSample ;
    if(colorSample.r > 0.75){
        tempSample.r = 0.75;
    }
    else if(colorSample.r > 0.5){
        tempSample.r = 0.5;
    }
    else if(colorSample.r > 0.25){
        tempSample.r = 0.25;
    }
    else{
        tempSample.r = 0;
    }

    if(colorSample.g > 0.75){
        tempSample.g = 0.75;
    }
    else if(colorSample.g > 0.5){
        tempSample.g = 0.5;
    }
    else if(colorSample.g > 0.25){
        tempSample.g = 0.25;
    }
    else{
        tempSample.g = 0;
    }

    if(colorSample.b > 0.75){
        tempSample.b = 0.75;
    }
    else if(colorSample.b > 0.5){
        tempSample.b = 0.5;
    }
    else if(colorSample.b > 0.25){
        tempSample.b = 0.25;
    }
    else{
        tempSample.b = 0;
    }
    return tempSample;
}

vec3 blackandwhite(vec3 inputcolor){
    float avg = (inputcolor.r + inputcolor.g + inputcolor.b)/3;
    return vec3(avg,avg,avg);
}

void main(){
   //color = vec3(0.18,0.58,0.18);
   if(fragmentColor == vec3(0.0,0.0,0.0)){
       color = vec3(1.0,0.5,1.0);
   }
   else{
        color = fragmentColor;
   }
    //color = getColor(fragmentColor);
    //vec3 temp = getColor(fragmentColor);
    //color = blackandwhite(temp);
}

