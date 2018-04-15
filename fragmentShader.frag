#version 130

in vec3 position;
in vec3 fragmentcolor;

out vec3 color;

uniform float time;
uniform float lightPositionx;
uniform float lightPositiony;
uniform int condition;
uniform int staticDrawing;


void main(){
    if(staticDrawing == 0)
    {
        float distance = sqrt((position.x - lightPositionx)*(position.x - lightPositionx)  + (position.y - lightPositiony)*(position.y - lightPositiony));
        if(condition == 0){
            if(distance < 0.3){
                color = vec3(
                abs(sin(time) + 1  + position.x*2 +  0.5 ) / (distance*100) , 
                abs(cos(time+ 3 )*sin(time - 3) + position.y*position.x*4/3 + 0.5 )/ (distance*100/3) , 
                abs(sin(time/2) + cos(time*2)  + position.x*2 + position.y*2  + 0.5 )/(distance*100)
                );  
            }
            else{
                color = vec3(
                abs(sin(time) + 1  + position.x*2 +  0.5 )/30, 
                abs(cos(time+ 3 )*sin(time - 3) + position.y*position.x*4/3 + 0.5 )/10 , 
                abs(sin(time/2) + cos(time*2)  + position.x*2 + position.y*2  + 0.5 )/30   
                );
            }
        }
        else if(condition == 1 ){
            color = vec3(
            abs(sin(time) + 1  + position.x*2 +  0.5 )/3, 
            abs(cos(time+ 3 )*sin(time - 3) + position.y*position.x*4/3 + 0.5 ) , 
            abs(sin(time/2) + cos(time*2)  + position.x*2 + position.y*2  + 0.5 )/3   
            );
        }
        else if(condition == 2){
            if(distance < 0.3){
                color = vec3(
                    abs(sin(time) + 1  + position.x*2 +  0.5 )/3 * sqrt(distance/0.3) , 
                    abs(cos(time+ 3 )*sin(time - 3) + position.y*position.x*4/3 + 0.5 ) * sqrt(distance/0.3) , 
                    abs(sin(time/2) + cos(time*2)  + position.x*2 + position.y*2  + 0.5 )/3  *sqrt(distance/0.3)
                ); 
            }
            else{
                color = vec3(
                    abs(sin(time) + 1  + position.x*2 +  0.5 )/3, 
                    abs(cos(time+ 3 )*sin(time - 3) + position.y*position.x*4/3 + 0.5 ) , 
                    abs(sin(time/2) + cos(time*2)  + position.x*2 + position.y*2  + 0.5 )/3   
                );
            }
        }
        else if(condition == 4){
            color = vec3(
            1 - abs(sin(time) + 1  + position.x*2 +  0.5 )/3, 
            1 - abs(cos(time+ 3 )*sin(time - 3) + position.y*position.x*4/3 + 0.5 ) , 
            1 - abs(sin(time/2) + cos(time*2)  + position.x*2 + position.y*2  + 0.5 )/3   
            );
        }
        //color = vec3(abs(sin(time)),abs(cos(time)),abs(sin(time)+cos(time))/2);
        return ;
    }
    color = fragmentcolor;
}

