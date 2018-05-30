Adding sprites

1.) declare Sprite
Sprite mySprite;

2.) initialize sprite:

static:
mySprite = new Sprite("fileName",x,y);
mySprite = new Sprite("fileName",x,y,width,height);

animated:
mySprite = new Sprite("fileName",widthInFrames,heightInFrames,speed,x,y);
mySprite = new Sprite("fileName",widthInFrames,heightInFrames,speed,x,y,width.height);

*speed means how many frames will pass before it will move to the next frame, high speed = low animation speed

**sketch width and height is 500, the point (0,0) is located in the upper left corner

3.) Tell sketch to draw sprite and animate in scene:

mySprite.render();
(if animation)
mySprite.incrementFrame();

