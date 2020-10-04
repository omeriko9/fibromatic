$.ready(function() {
    $('#chkLoop').bootstrapToggle();


  });

    if (!!window.EventSource) {
        
        var source = new EventSource('listener')
        console.log("Starting listener, source: " + source);
        
        source.onmessage = function(e) {
          console.log(e.data);
          switch(e.data){
            case "starting:": break;
            case "ended": after(); break;
            case "killed": after(); break;
          }
        };

        source.addEventListener('open', function(e) {
          console.log("Listener Started");
        }, false)

        source.addEventListener('error', function(e) {
          if (e.eventPhase == EventSource.CLOSED)
          {
            console.log("Listener error - closing");
            source.close()
          }
          if (e.target.readyState == EventSource.CLOSED) {
            console.log("Listener Disconnected");
          }
          else if (e.target.readyState == EventSource.CONNECTING) {
            console.log("Listener Connecting...");
          }
        }, false)
      } else {
        alert("Your browser doesn't support SSE");
    }


function vol() {
    
    $('.modal').modal('show');
    $.ajax({
        url: "/vol",
        type: "get",
        data: {
            percentage: $(".input-number").val(), 
        }, 
        success: function(returned) {
            console.log('vol returned: ' + returned); 
            //after();
            $('.modal').modal('hide');

        },
        error: function() {
            $('.modal').modal('hide');
            //after();
        }
    });
    //$('.modal').modal('hide');
    return false;
}

function act(val){
    
    console.log("client act, val: " + $('#command').val());
    //$('button').prop('disabled', true);
    $('.btnkill').css('display','block').prop('disabled',false);
    $('.modal').modal('show');
    $.ajax({
        url: "/act",
        type: "get",
        data: {
            name: val, 
            value: $('#command').val()
            // random: $('#random').is(':checked'), 
            // loop: $('#loop').is(':checked'),
            // rndmin: $('#rndmin').val(),
            // rndmax: $('#rndmax').val()
        }, 
        success: function(returned) {
            console.log(returned); 
            $('.modal').modal('hide');
            //after();
        },
        error: function() {
            console.log("error: ");
            $('.modal').modal('hide');
            //after();
        }
    });

    return false;
}

function kill(){
    $('.modal').modal('show');
    $.ajax({
        url: "/kill",
        type: "get",
        success: function(returned) {
            console.log(returned); 
            after();
            console.log("hide");
            $('.modal').modal('hide');
        },
        error: function() {
            after();
            $('.modal').modal('hide');
        }
    });

    return false;

}

function after(){
  //$('.btnkill').css('display','none');
  $('button').prop('disabled', false);

}

jQuery(document).ready(function($) {    

    
        //plugin bootstrap minus and plus
        //http://jsfiddle.net/laelitenetwork/puJ6G/
        $('.btn-number').click(function(e){
            
            e.preventDefault();
            
            fieldName = $(this).attr('data-field');
            type      = $(this).attr('data-type');
            var input = $("input[name='"+fieldName+"']");
            var currentVal = parseInt(input.val());
            if (!isNaN(currentVal)) {
                if(type == 'minus') {
                    
                    if(currentVal > input.attr('min')) {
                        input.val(currentVal - 5).change();
                    } 
                    if(parseInt(input.val()) == input.attr('min')) {
                        $(this).attr('disabled', true);
                    }

                } else if(type == 'plus') {

                    if(currentVal < input.attr('max')) {
                        input.val(currentVal + 5).change();
                    }
                    if(parseInt(input.val()) == input.attr('max')) {
                        $(this).attr('disabled', true);
                    }

                }
            } else {
                input.val(0);
            }
        });
        $('.input-number').focusin(function(){
           $(this).data('oldValue', $(this).val());
        });
        $('.input-number').change(function() {
            
            minValue =  parseInt($(this).attr('min'));
            maxValue =  parseInt($(this).attr('max'));
            valueCurrent = parseInt($(this).val());
            
            name = $(this).attr('name');
            if(valueCurrent >= minValue) {
                $(".btn-number[data-type='minus'][data-field='"+name+"']").removeAttr('disabled')
            } else {
                //alert('Sorry, the minimum value was reached');
                $(this).val($(this).data('oldValue'));
            }
            if(valueCurrent <= maxValue) {
                $(".btn-number[data-type='plus'][data-field='"+name+"']").removeAttr('disabled')
            } else {
                //alert('Sorry, the maximum value was reached');
                $(this).val($(this).data('oldValue'));
            }
            
            
        });
        $(".input-number").keydown(function (e) {
                // Allow: backspace, delete, tab, escape, enter and .
                if ($.inArray(e.keyCode, [46, 8, 9, 27, 13, 190]) !== -1 ||
                     // Allow: Ctrl+A
                    (e.keyCode == 65 && e.ctrlKey === true) || 
                     // Allow: home, end, left, right
                    (e.keyCode >= 35 && e.keyCode <= 39)) {
                         // let it happen, don't do anything
                         return;
                }
                // Ensure that it is a number and stop the keypress
                if ((e.shiftKey || (e.keyCode < 48 || e.keyCode > 57)) && (e.keyCode < 96 || e.keyCode > 105)) {
                    e.preventDefault();
                }
            });
    });