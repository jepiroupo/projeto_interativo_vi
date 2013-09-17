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

    for (i=0; i < numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();
        //console.log("left: " + pos.left + " top: " + pos.top);
        if (pos.left == 0 || pos.left == 1600 || pos.top == 0 || pos.top == 1184){
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

function gerarXML(){

    var numLis = 0;
    $("#lista").find("li").each(function(){
        numLis += 1;
    });

    var string;
    string = "";
    var stringXML;
    stringXML = "<dados>";
    for (i=0; i < numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();

        if ($(button).hasClass('caminho')){
            string += pos.left + "|" + pos.top + "|" + "caminho" + "\n";
            stringXML += "<info> \n";
            stringXML += "<classe>caminho</classe> \n";
            stringXML += "<left>"+pos.left+"</left> \n";
            stringXML += "<top>"+pos.top+"</top> \n";
            stringXML += "</info> \n"
        }
        else if ($(button).hasClass('parede')){
            string += pos.left + "|" + pos.top + "|" + "parede" + "\n";
            stringXML += "<info> \n";
            stringXML += "<classe>parede</classe> \n";
            stringXML += "<left>"+pos.left+"</left> \n";
            stringXML += "<top>"+pos.top+"</top> \n";
            stringXML += "</info> \n"
        }
        else if ($(button).hasClass('vermelho')){
            string += pos.left + "|" + pos.top + "|" + "vermelho" + "\n";
            stringXML += "<info> \n";
            stringXML += "<classe>vermelho</classe> \n";
            stringXML += "<left>"+pos.left+"</left> \n";
            stringXML += "<top>"+pos.top+"</top> \n";
            stringXML += "</info> \n"
        }
        else if ($(button).hasClass('azul')){
            string += pos.left + "|" + pos.top + "|" + "azul" + "\n";
            stringXML += "<info> \n";
            stringXML += "<classe>caminho</classe> \n";
            stringXML += "<left>"+pos.left+"</left> \n";
            stringXML += "<top>"+pos.top+"</top> \n";
            stringXML += "</info> \n"
        }
        else if ($(button).hasClass('verde')){
            string += pos.left + "|" + pos.top + "|" + "verde" + "\n";
            stringXML += "<info> \n";
            stringXML += "<classe>caminho</classe> \n";
            stringXML += "<left>"+pos.left+"</left> \n";
            stringXML += "<top>"+pos.top+"</top> \n";
            stringXML += "</info> \n"
        }
        else if ($(button).hasClass('amarelo')){
            string += pos.left + "|" + pos.top + "|" + "amarelo" + "\n";
            stringXML += "<info> \n";
            stringXML += "<classe>caminho</classe> \n";
            stringXML += "<left>"+pos.left+"</left> \n";
            stringXML += "<top>"+pos.top+"</top> \n";
            stringXML += "</info> \n"
        }
    }
    console.log(string);
}