dados = {

    labirinto: function (xml){
        //<background>
        width = [], height = [],

        $(xml).find("parede").each(function()
        {
            $('<li class="caminho" style="background-image: url(\'imgs/paredes.png\')"></li>').appendTo('#lista');

        });

        var numLis = 0;
        $("#lista").find("li").each(function(){
            numLis += 1;
        });

        $("#lista").width(String(width[0]).split("px").join("") * numLis);

        init();
    }
}

function init () {

    $("#lista").find("li").click(listaClick);

    var numLis = 0;
        $("#lista").find("li").each(function(){
            numLis += 1;
        });

    for (i=0; numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();
        if (pos.left == 0 || pos.left == 1600 || pos.left == 1312 || pos.top == 0 || pos.top == 1184){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
        if (pos.left == 640 && pos.top == 608){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
    }

    function listaClick (e) {
        e.preventDefault();

        navigate($(this).index());
    }

    function navigate(id){
        var button =  $("#lista").find("li")[id];

        if ($(button).hasClass('caminho')){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
        else if ($(button).hasClass('parede')){
            $(button).removeClass('parede');
            $(button).addClass('vermelho');
        }
        else if ($(button).hasClass('vermelho')){
            $(button).removeClass('vermelho');
            $(button).addClass('azul');
        }
        else if ($(button).hasClass('azul')){
            $(button).removeClass('azul');
            $(button).addClass('verde');
        }
        else if ($(button).hasClass('verde')){
            $(button).removeClass('verde');
            $(button).addClass('amarelo');
        }
        else if ($(button).hasClass('amarelo')){
            $(button).removeClass('amarelo');
            $(button).addClass('caminho');
        }

        var pos = $(button).offset();
        console.log("left: " + pos.left + " top: " + pos.top);
    }
}