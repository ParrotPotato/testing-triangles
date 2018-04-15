#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

using std::cout ;
using std::cin ;
using std::endl;




int main(){
    ////TRANSLATION///
    glm::mat4 matrix(1);
    matrix = glm::translate(glm::vec3(10.0,0.0,0.0));
    glm::vec4 position(10.0,10.0,10.0,1.0);
    glm::vec4 finalPosition = matrix * position ;
    cout << "finalPosition(x,y,z) = (" << finalPosition.x << ',' << finalPosition.y << ',' << finalPosition.z << ")" << endl;
    ///IDENTITY MATRIX///
    glm::mat4 matrix2 = glm::mat4(1.0f);
    ///SCALING MATRIX///
    glm::mat4 scalingMatrix = glm::scale(glm::vec3(2.0,2.0,2.0));
    return 0;
}