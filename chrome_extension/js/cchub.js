/**
 * Created by hubert on 25.10.14.
 */
"use strict";

$(function () {
    var url = window.location.href;
    var re = /.*github\.com\/([^\/]+)\/([^\/]+)\/pull\/([^/]+)\/.*/;

    var tokens = url.match(re);
    var user = tokens[1];
    var repo = tokens[2];
    var pull = tokens[3];

    //var requestUrl = "http://students.mimuw.edu.pl:8080/client/" + user + "/" + repo + "/" + pull;
    var requestUrl = "http://students.mimuw.edu.pl/~rp335451/test.json";


    $('#toc').append('<div id="cchub-top-info" class="file"></div>');

    $.get(requestUrl)
        .done(function (result) {
            setUpElements();
            applyNotifications(result);
        })
        .fail(function (errmsg) {
            console.log(errmsg);
        });
});

function setUpElements() {
    $('body').append('<div id="scrollbar-hint"></div>');
    $('#cchub-top-info')
        .append(
            '<div class="meta">' +
                '<div class="info">' +
                    '<strong>CCHub validation statistics</strong>: <strong id="#cchub-total-msg">0</strong> messages (including <strong>0</strong> errors)' +
                '</div>' +
                '<div id="cchub-tabs" class="actions"></div>' +
            '</div>')
        .append(
            '<div id="cchub-tabs-content"></div>'
        );
}

function applyNotifications(data) {
    var notifMap = {};
    var files = data.files;
    //console.log(files);

    files.forEach(function (item) {
        item.notifications.forEach(function (notif) {
            var b = $('.blob-code b[data-path="' + item.filename + '"][data-line="' + notif.line + '"]');

            b.parent().parent().addClass('cchub-notification');

            var moreBtn = $(
                '<div class="cchub-more-btn">' +
                    '<div class="cchub-tooltip">' + notif.content + '</div>' +
                '</div>');

            b.parent().append(moreBtn);

            var top = moreBtn.offset().top;
            var height = $('body').height();
            var hint = document.createElement('div');
            $(hint).addClass('item');
            $(hint).css('top',top / height * 100 + '%');
            $(hint).appendTo($('#scrollbar-hint'));

            notif.type.forEach(function (type) {
                // Add notification to map to display overall statistics
                if (!notifMap.hasOwnProperty(notif.type))
                    notifMap[notif.type] = [];

                notifMap[notif.type].push({
                    content: notif.content,
                    element: moreBtn
                });

                b.parent().children('.cchub-more-btn:last-child').append(
                    '<div class="cchub-icon cchub-' + type + '"></div>'
                );
                b.parent().parent().addClass('cchub-' + type);
            });
        });
    });

    console.log(notifMap);

    for (var key in notifMap) {
        //console.log(key);
        var tab = $('<div class="cchub-tab" data-tabid="cchub-tab-' + key + '"><div class="cchub-icon cchub-' + key + '"></div></div>');
        var content = $('<div id="cchub-tab-' + key + '" class="cchub-notif-list"></div>');
        //console.log($('#cchub-tabs'));
        $('#cchub-tabs').append(tab);
        $('#cchub-tabs-content').append(content);




//        tab.click(function(e) {
//            $('.cchub-tab').removeClass('cchub-active');
//            console.log($(e.currentTarget));
//            $(this).attr('data-tabid').addClass('sshub-active');
//            //$(e.currentTarget[0]).data('tabid').addClass('cchub-active');
//
//        })

        notifMap[key].forEach(function(el) {
            console.log(el);
            var listItem = $('<div>' + el.content + '</div>');
            listItem.appendTo(content);
            listItem.click(function (e) {
                $('html, body').stop().animate({
                    'scrollTop': Math.max(0, el.element.offset().top - 200)
                }, 900, 'swing');
                el.element.addClass('cchub-active');
                setTimeout(function() {
                    el.element.removeClass('cchub-active');
                }, 3000);
            });
        });
    }

    $('#cchub-tabs .cchub-tab').click(function(){
        var tab_id = $(this).attr('data-tabid');

        console.log(tab_id);
        $('#cchub-tabs-content>div').removeClass('cchub-active');
        $('#cchub-tabs .cchub-tab').removeClass('cchub-active');

        $(this).addClass('cchub-active');
        $("#"+tab_id).addClass('cchub-active');
    });
}