#include "Hud.h"

Hud::Hud()
{
    _texture_name.loadFromFile("Resourses/Cartel.png");
    _texture_arrow.loadFromFile("Resourses/Paquete_flechas.png");
    _texture_paper.loadFromFile("Resourses/Papel_HUD.png");
    _texture_name.setSmooth(true);
    _texture_arrow.setSmooth(true);
    _texture_paper.setSmooth(true);

    _sprite_name.setTexture(_texture_name);
    _sprite_arrow.setTexture(_texture_arrow);
    _sprite_paper.setTexture(_texture_paper);

    lifeBar_initTexture();

    _sprite_paper.setScale(.8f,.8f);
    _sprite_arrow.setScale(.5f,.5f);


    if (!_font.loadFromFile("Resourses/Font/PressStart2P-Regular.ttf"))
    {
        std::cout<<"Error al cargar texto"<<std::endl;
    }

    _text_name.setFont(_font);
    _text_name.setFillColor(sf::Color(235, 235, 235));
    _text_name.setCharacterSize(10.f);

    _text_arrow.setFont(_font);
    _text_arrow.setFillColor(sf::Color(71, 72, 71));
    _text_arrow.setCharacterSize(19.f);

    _text_score.setFont(_font);
    _text_score.setFillColor(sf::Color(71, 72, 71));
    _text_score.setCharacterSize(12.f);
    _text_score.setString("Score");

    _text_score_n.setFont(_font);
    _text_score_n.setFillColor(sf::Color(71, 72, 71));
    _text_score_n.setCharacterSize(12.f);

    _text_lives.setFont(_font);
    _text_lives.setFillColor(sf::Color(71, 72, 71));
    _text_lives.setCharacterSize(12.f);
    _text_lives.setString("Vidas");

    _text_lives_n.setFont(_font);
    _text_lives_n.setFillColor(sf::Color(71, 72, 71));
    _text_lives_n.setCharacterSize(12.f);


}

Hud::~Hud()
{

}


void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite_name, states);
    target.draw(_text_name, states);
    target.draw(_sprite_energyBar, states);
    target.draw(_sprite_paper, states);
    target.draw(_sprite_arrow, states);
    target.draw(_text_arrow, states);
    target.draw(_text_score, states);
    target.draw(_text_score_n, states);
    target.draw(_text_lives, states);
    target.draw(_text_lives_n, states);

}

void Hud::mobility(const sf::Vector2f& heroPosition,const sf::Vector2f& camaraPosition)
{
    _sprite_name.setPosition(heroPosition.x-500,camaraPosition.y-310);
    _text_name.setPosition(heroPosition.x-460,camaraPosition.y-245);
    _sprite_energyBar.setPosition(heroPosition.x-300,camaraPosition.y-290);
    _sprite_paper.setPosition(heroPosition.x+350,camaraPosition.y-300);
    _sprite_arrow.setPosition(heroPosition.x+420,camaraPosition.y-260);
    _text_score.setPosition(heroPosition.x+390,camaraPosition.y-270);
    _text_score_n.setPosition(heroPosition.x+390,camaraPosition.y-250);
    _text_lives.setPosition(heroPosition.x+390,camaraPosition.y-230);
    _text_lives_n.setPosition(heroPosition.x+390,camaraPosition.y-210);
    _text_arrow.setPosition(heroPosition.x+495,camaraPosition.y-210);
}

void Hud::update(const std::string& n,int e,int v, int p, int a)
{
    arrow=a;
    score=p;
    lives=v;
    energy=e;
    _text_name.setString(n);
    _text_arrow.setString(std::to_string(arrow));
    _text_score_n.setString(std::to_string(score));
    _text_lives_n.setString(std::to_string(lives));

    lifeBar_update(energy);

}

void Hud::lifeBar_initTexture()
{
    _texture_energyBar.loadFromFile("Resourses/Energy_bar.png");
    _texture_energyBar.setSmooth(true);
    _sprite_energyBar.setTexture(_texture_energyBar);
    _current_frame=sf::IntRect(0,0,630,72);
    _sprite_energyBar.setTextureRect(_current_frame);
}

void Hud::lifeBar_update(int l)
{

    float a=72;

    if (l==100)
    {
        _current_frame=sf::IntRect(0,0,630,a);

    }
    else if(l<=100&&l>90)
    {
        _current_frame=sf::IntRect(0,0,630,a);


    }
    else if(l<=90&&l>80)
    {
        _current_frame=sf::IntRect(0,72,630,a);

    }
    else if(l<=80&&l>70)
    {
        _current_frame=sf::IntRect(0,144,630,a);

    }
    else if(l<=70&&l>60)
    {
        _current_frame=sf::IntRect(0,216,630,a);

    }
    else if(l<=70&&l>60)
    {
        _current_frame=sf::IntRect(0,288,630,a);

    }
    else if(l<=60&&l>50)
    {
        _current_frame=sf::IntRect(0,360,630,a);

    }
    else if(l<=50&&l>40)
    {
        _current_frame=sf::IntRect(0,432,630,a);

    }
    else if(l<=40&&l>30)
    {
        _current_frame=sf::IntRect(0,504,630,a);

    }
    else if(l<=30&&l>20)
    {
        _current_frame=sf::IntRect(0,576,630,a);

    }
    else if(l<=20&&l>10)
    {
        _current_frame=sf::IntRect(0,648,630,a);

    }
    else if(l<=10&&l>0)
    {
        _current_frame=sf::IntRect(0,720,630,a);

    }
    else if(l==0)
    {
        _current_frame=sf::IntRect(0,720,630,a);

    }
    _sprite_energyBar.setTextureRect(_current_frame);
}
