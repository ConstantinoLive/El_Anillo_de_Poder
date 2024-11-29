#include "Anillos.h"

Anillos::Anillos()
{
    _texture_anillos.loadFromFile("Resourses/Anillos.png");
    _spriteAnillos.setTexture(_texture_anillos);
    _spriteAnillos.setPosition(250, 555); // posición inicial
    _spriteAnillos.setScale(sf::Vector2f(0.5f, 0.5f));

    _state = STATES::APPEARED_GOLD;
    EstadoAnterior=1;
    _visibleTime = sf::seconds(3.f);
    _invisibleTime = sf::seconds(2.f);
    _timer.restart();
    _isVisible = true;


    _animationSpeed = 0.1f;
    _width_texture = 66;
    _end_of_frames_sheet = 6 * _width_texture;
}

Anillos::~Anillos()
{
    //dtor
}

void Anillos::limitePantalla(const sf::Vector2f& heroPosition){

    if (_spriteAnillos.getPosition().x<250){
        _spriteAnillos.setPosition (250,getPosition().y);

    }
    if (_spriteAnillos.getPosition().x>13250){
        _spriteAnillos.setPosition (13250,getPosition().y);

    }
    if(heroPosition.y<500)
    {
        if (_spriteAnillos.getPosition().x>822&&_spriteAnillos.getPosition().x<1386){
            _spriteAnillos.setPosition(822,getPosition().y);
        }
        if (_spriteAnillos.getPosition().x>4146&&_spriteAnillos.getPosition().x<4700){
            _spriteAnillos.setPosition (4146,getPosition().y);
        }
        if (_spriteAnillos.getPosition().x>9546&&_spriteAnillos.getPosition().x<9842){
            _spriteAnillos.setPosition (9546,getPosition().y);
        }
        if (_spriteAnillos.getPosition().x>10858&&_spriteAnillos.getPosition().x<11158){
            _spriteAnillos.setPosition (10858,getPosition().y);
        }
    }
}

void Anillos::update(const sf::Vector2f& heroPosition)
{
    limitePantalla(heroPosition);

    if (_isVisible) {
        updateAnimation();

        if (_timer.getElapsedTime() >= _visibleTime) {
            _isVisible = false;
            _state = STATES::DISAPPEARED;
            _timer.restart();
            initVariables();
        }
    }
    else {
        if (_timer.getElapsedTime() >= _invisibleTime) {
            if (_state == STATES::DISAPPEARED) {
                if(EstadoAnterior==1){
                _state = STATES::APPEARED_GOLD;
                _isVisible = true;
                _timer.restart();
                initVariables();
                EstadoAnterior=0;}
                else{
                _state = STATES::APPEARED_SILVER;
                _isVisible = true;
                _timer.restart();
                initVariables();
                EstadoAnterior=1;
                }

                if (_state == STATES::APPEARED_GOLD) {
                    _spriteAnillos.setPosition(250, 555);
                } else {
                    _spriteAnillos.setPosition(350, 555);
                }
                float offset = (rand()%2!=0) ? -350 : 350;

                if(heroPosition.y<=500)
                {
                    _spriteAnillos.setPosition(heroPosition.x + offset, 555);
                }
                else{
                    _spriteAnillos.setPosition(heroPosition.x + offset, 1280);
                }
        }
    }
}}



sf::Sprite& Anillos::getDraw()
{
    return _spriteAnillos;
}

sf::Vector2f Anillos::getPosition()
{
    return _spriteAnillos.getPosition();
}

void Anillos::setPosition(float x, float y)
{
    _spriteAnillos.setPosition(x, y);
}

void Anillos::updateAnimation()
{
    if (_animationTimer.getElapsedTime().asSeconds() >= _animationSpeed)
    {
        _current_frame.left += _width_texture;

        if (_current_frame.left >= _end_of_frames_sheet) {
            _current_frame.left = 0; // Reiniciar al primer frame
        }

        if (_isVisible) {
            _spriteAnillos.setTextureRect(_current_frame);
        }

        _animationTimer.restart();
    }
}

void Anillos::initVariables()
{
    switch (_state)
    {
    case APPEARED_GOLD:
        _current_frame = sf::IntRect(0, 0, _width_texture, 66); // Frame inicial dorado
        break;

    case APPEARED_SILVER:
        _current_frame = sf::IntRect(0, 66, _width_texture, 132); // Frame inicial plateado
        break;

    case DISAPPEARED:
        _spriteAnillos.setScale(sf::Vector2f(0, 0)); // Escala a cero
        break;
    }

    if (_state == APPEARED_GOLD || _state == APPEARED_SILVER) {
        _spriteAnillos.setScale(sf::Vector2f(0.5f, 0.5f));
    }
}
sf::FloatRect Anillos::getBounds() const {
        return _spriteAnillos.getGlobalBounds();
}
