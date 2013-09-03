dados = {

    labirinto: function (xml){
        //<background>
        width = [], height = [],

        $(xml).find("parede").each(function()
        {
            $('<li class="button" style="background-image: url(\'imgs/paredes.jpg\')"></li>').appendTo('#lista');

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
    var botaoWidth = "32";
    var botaoHeight = "32";

    //Estados do botão
    var atual = "-" + botaoWidth + "px 0px";
    var visto = "-" + (botaoWidth*2) + "px 0px";

    var lastButton = -1;
    var currentButton;
    var visiteds = [];

    $("#lista").find("li").css("width", botaoWidth+"px");
    $("#lista").find("li").css("height", botaoHeight+"px");

    $("#lista").find("li").click(listaClick);

    for(var i = 0; i < $("#lista").find("li").length; i++) visiteds.push({obj : $(this), visited : false});

    navigate(0);

    // fim barra de crédito
    function listaClick (e) {

        // if(lastButton != -1){
        //     var button =  $(this).parent().find("li")[currentButton];
        //     $(button).css("background-position", visto);
        // }

        e.preventDefault();

        navigate($(this).index());
    }

    function navigate(id){

        //Botão atual
        currentButton = id;
        lastButton = id;

        visiteds[id].visited = true;
        var button =  $("#lista").find("li")[id];
        $(button).css("background-position", atual);
    }
}