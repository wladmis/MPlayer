






// Translated by:  Volodymyr M. Lisivka <lvm@mystery.lviv.net>,
// Andriy Gritsenko <andrej@lucky.net>
// sevenfourk <sevenfourk@gmail.com>
// Led <ledest@gmail.com>

// Was synced with help_mp-en.h: 1.1.1

// ========================= MPlayer help ===========================

#ifdef CONFIG_VCD
#define MSGTR_HelpVCD " vcd://<номер треку> грати VCD (video cd) трек з пристрою замість файлу\n"
#else
#define MSGTR_HelpVCD
#endif

#ifdef CONFIG_DVDREAD
#define MSGTR_HelpDVD " dvd://<номер титрів> грати DVD титри/трек з пристрою замість файлу\n"
#else
#define MSGTR_HelpDVD
#endif

#define MSGTR_Help \
"Запуск:   mplayer [опції] [path/]filename\n"\
"\n"\
"Опції:\n"\
" -vo <drv[:dev]> вибір драйвера і пристрою відео виводу (список див. з '-vo help')\n"\
" -ao <drv[:dev]> вибір драйвера і пристрою аудіо виводу (список див. з '-ao help')\n"\
MSGTR_HelpVCD \
MSGTR_HelpDVD \
" -alang/-slang   вибрати мову DVD аудіо/субтитрів (двосимвольний код країни)\n"\
" -ss <час>       переміститися на задану (секунди або ГГ:ХХ:СС) позицію\n"\
" -nosound        без звуку\n"\
" -fs -vm -zoom   повноекранне програвання (повноекр.,зміна відео,масштабування\n"\
" -x <x> -y <y>   маштабувати картинку до <x> * <y> [якщо -vo драйвер підтримує!]\n"\
" -sub <file>     вказати файл субтитрів (див. також -subfps, -subdelay)\n"\
" -playlist <file> вказати playlist\n"\
" -vid x -aid y   опції для вибору відео (x) і аудіо (y) потоку для програвання\n"\
" -fps x -srate y опції для зміни відео (x кадр/сек) і аудіо (y Hz) швидкості\n"\
" -pp <quality>   дозволити фільтр (0-4 для DivX, 0-63 для mpegs)\n"\
" -framedrop      дозволити втрату кадрів (для повільних машин)\n"\
"\n"\
"Клавіші:\n"\
" <-  або ->      перемотування вперед/назад на 10 секунд\n"\
" вверх або вниз  перемотування вперед/назад на  1 хвилину\n"\
" pgup або pgdown перемотування вперед/назад на 10 хвилин\n"\
" < або >         перемотування вперед/назад у списку програвання\n"\
" p або ПРОБІЛ    зупинити фільм (будь-яка клавіша - продовжити)\n"\
" q або ESC       зупинити відтворення і вихід\n"\
" + або -         регулювати затримку звуку по +/- 0.1 секунді\n"\
" o               циклічний перебір OSD режимів:  нема / навігація / навігація+таймер\n"\
" * або /         додати або зменшити гучність (натискання 'm' вибирає master/pcm)\n"\
" z або x         регулювати затримку субтитрів по +/- 0.1 секунді\n"\
" r or t          змінити положення субтитрів вгору/вниз, також див. -vf expand\n"\
"\n"\
" * * * ДЕТАЛЬНІШЕ ДИВ. ДОКУМЕНТАЦІЮ, ПРО ДОДАТКОВІ ОПЦІЇ І КЛЮЧІ! * * *\n"\
"\n"

static const char help_text[] = MSGTR_Help;

// ========================= MPlayer messages ===========================

// mplayer.c:
#define MSGTR_Exiting "\nВиходимо...\n"
#define MSGTR_ExitingHow "\nВиходимо... (%s)\n"
#define MSGTR_Exit_quit "Вихід"
#define MSGTR_Exit_eof "Кінець файлу"
#define MSGTR_Exit_error "Фатальна помилка"
#define MSGTR_IntBySignal "\nMPlayer перерваний сигналом %d у модулі: %s \n"
#define MSGTR_NoHomeDir "Не можу знайти домашній каталог\n"
#define MSGTR_GetpathProblem "проблеми у get_path(\"config\")\n"
#define MSGTR_CreatingCfgFile "Створення файлу конфігурації: %s\n"
#define MSGTR_CantLoadFont "Не можу завантажити шрифт: %s\n"
#define MSGTR_CantLoadSub "Не можу завантажити субтитри: %s\n"
#define MSGTR_DumpSelectedStreamMissing "dump: FATAL: обраний потік загублений!\n"
#define MSGTR_CantOpenDumpfile "Не можу відкрити файл дампу!!!\n"
#define MSGTR_CoreDumped "Створено дамп ядра :)\n"
#define MSGTR_DumpBytesWrittenPercent "дамп: %"PRIu64" байт(и) записано (~%.1f%%)\r"
#define MSGTR_DumpBytesWritten "дамп: %"PRIu64" байт(и) записано\r"
#define MSGTR_DumpBytesWrittenTo "дамп: %"PRIu64" байт(и) записано до '%s'.\n"
#define MSGTR_FPSnotspecified "Не вказано чи невірна кількість кадрів, застосуйте опцію -fps.\n"
#define MSGTR_TryForceAudioFmtStr "Намагаюсь форсувати групу аудіо кодеків %s...\n"
#define MSGTR_CantFindVideoCodec "Не можу знайти кодек для відео формату 0x%X!\n"
#define MSGTR_TryForceVideoFmtStr "Намагаюсь форсувати групу відео кодеків %s...\n"
#define MSGTR_CantFindVideoCodec "Не можгу знайти кодек для вибранного -vo та відеоформату 0x%X!\n"
#define MSGTR_CannotInitVO "ФАТАЛЬНО: Не можу ініціалізувати відео драйвер!\n"
#define MSGTR_CannotInitAO "не можу відкрити/ініціалізувати аудіо пристрій -> ГРАЮ БЕЗ ЗВУКУ\n"
#define MSGTR_StartPlaying "Початок програвання...\n"

#define MSGTR_SystemTooSlow "\n\n"\
"         ********************************************************\n"\
"         **** Ваша система надто ПОВІЛЬНА щоб відтворити це! ****\n"\
"         ********************************************************\n"\
"!!! Можливі причини, проблеми, обхідні шляхи: \n"\
"- Найбільш загальні: поганий/сирий _аудіо_ драйвер :\n"\
"  - спробуйте -ao sdl або використовуйте ALSA 0.5 або емуляцію oss на ALSA 0.9.\n"\
"  - Експеримент з різними значеннями для -autosync, спробуйте 30 .\n"\
"- Повільний відео вивід.\n"\
"  - спробуйте інший -vo драйвер (список: -vo help) або спробуйте з -framedrop!\n"\
"- Повільний ЦП. Не намагайтеся відтворювати великі dvd/divx на повільних\n"\
"  процесорах! спробуйте -hardframedrop\n"\
"- Битий файл. Спробуйте різні комбінації: -nobps  -ni  -mc 0  -forceidx\n"\
"- Повільний носій (диски NFS/SMB, DVD, VCD та ін.). Спробуйте -cache 8192.\n"\
"- Ви використовуєте -cache для програвання неперемеженого AVI файлу?\n"\
"  - спробуйте -nocache.\n"\
"Читайте поради в файлах DOCS/HTML/en/video.html .\n"\
"Якщо нічого не допомогло, тоді читайте DOCS/HTML/en/bugreports.html!\n\n"

#define MSGTR_NoGui "MPlayer був скомпільований БЕЗ підтримки GUI!\n"
#define MSGTR_GuiNeedsX "MPlayer GUI вимагає X11!\n"
#define MSGTR_Playing "\nПрогравання %s\n"
#define MSGTR_NoSound "Аудіо: без звуку!!!\n"
#define MSGTR_FPSforced "Примусово змінена кількість кадрів на секунду на %5.3f (ftime: %5.3f)\n"
#define MSGTR_AvailableVideoOutputDrivers "Доступні модулі відео виводу:\n"
#define MSGTR_AvailableAudioOutputDrivers "Доступні модулі аудіо виводу:\n"
#define MSGTR_AvailableAudioCodecs "Доступні аудіо кодеки:\n"
#define MSGTR_AvailableVideoCodecs "Доступні відео кодеки:\n"
#define MSGTR_AvailableAudioFm "Доступні (вбудовані) групи/драйвера аудіо кодеків:\n"
#define MSGTR_AvailableVideoFm "Доступні (вбудовані) групи/драйвера відео кодеків:\n"
#define MSGTR_AvailableFsType "Доступні варіанти повноекранного відеорежиму:\n"
#define MSGTR_CannotReadVideoProperties "Відео: Неможливо отримати властивості.\n"
#define MSGTR_NoStreamFound "Потік не знайдено.\n"
#define MSGTR_ErrorInitializingVODevice "Помилка відкриття/ініціалізації вибраного video_out (-vo) пристрою.\n"
#define MSGTR_ForcedVideoCodec "Примусовий відео кодек: %s\n"
#define MSGTR_ForcedAudioCodec "Примусовий аудіо кодек: %s\n"
#define MSGTR_Video_NoVideo "Відео: без відео\n"
#define MSGTR_NotInitializeVOPorVO "\nFATAL: Неможливо ініціалізувати відео фільтри (-vf) або відео вивід (-vo).\n"
#define MSGTR_Paused "  =====  ПАУЗА  ====="
#define MSGTR_PlaylistLoadUnable "\nНеможливо завантажити playlist %s.\n"
#define MSGTR_Exit_SIGILL_RTCpuSel \
"- MPlayer зламався через 'Невірні інструкції'.\n"\
"  Може бути помилка у вашому новому коду визначення типу CPU...\n"\
"  Будь-ласка перегляньте DOCS/HTML/en/bugreports.html.\n"
#define MSGTR_Exit_SIGILL \
"- MPlayer зламався через 'Невірні інструкції'.\n"\
"  Іноді таке трапляється під час запуску програвача на CPU що відрізняється від того, на якому він\n"\
"  був зібраний/оптимізований.\n  Перевірте!\n"
#define MSGTR_Exit_SIGSEGV_SIGFPE \
"- MPlayer зламався через невірне використання CPU/FPU/RAM.\n"\
"  Зберіть знову MPlayer з --enable-debug а зробіть 'gdb' backtrace та\n"\
"  дизасемблювання. Для довідок, перегляньте DOCS/HTML/en/bugreports_what.html#bugreports_crash\n"
#define MSGTR_Exit_SIGCRASH \
"- MPlayer зламався. Цього не повинно було трапитися.\n"\
"  Може бути помилка у коді MPlayer _або_ ваших драйверах _або_ через\n"\
"  версію gcc. Якщо важаєте що, це помилка MPlayer, будь-ласка читайте\n"\
"  DOCS/HTML/en/bugreports.html та слідкуєте інструкціям. Ми можемо\n"\
"  допомогти лише у разі забезпечення інформація коли доповідаєте про помилку.\n"
#define MSGTR_LoadingConfig "Завантаження конфігурації '%s'\n"
#define MSGTR_LoadingProtocolProfile "Завантаження профілю для протоколу '%s'\n"
#define MSGTR_LoadingExtensionProfile "Завантаження профілю для розширення '%s'\n"
#define MSGTR_AddedSubtitleFile "СУБТИТРИ: Додано файл субтитрів (%d): %s\n"
#define MSGTR_RemovedSubtitleFile "СУБТИТРИ: Видалено файл субтитрів (%d): %s\n"
#define MSGTR_RTCDeviceNotOpenable "Не можу відкрити %s: %s (користувач повинен мати права читання для файлу.)\n"
#define MSGTR_LinuxRTCInitErrorIrqpSet "Помилка ініцілізації Linux RTC у ioctl (rtc_irqp_set %lu): %s\n"
#define MSGTR_IncreaseRTCMaxUserFreq "Спробуйте додати \"echo %lu > /proc/sys/dev/rtc/max-user-freq\" до скриптів запуску системи.\n"
#define MSGTR_LinuxRTCInitErrorPieOn "Помилка ініціалізації Linux RTC у ioctl (rtc_pie_on): %s\n"
#define MSGTR_Getch2InitializedTwice "ПОПЕРЕДЖЕННЯ: getch2_init визвано двічі!\n"
#define MSGTR_CantOpenLibmenuFilterWithThisRootMenu "Не можу відкрити відео фільтр libmenu з цим кореневим меню %s.\n"
#define MSGTR_AudioFilterChainPreinitError "Помилка у ланці pre-init аудіо фільтру!\n"
#define MSGTR_LinuxRTCReadError "Помилка читання Linux RTC: %s\n"
#define MSGTR_SoftsleepUnderflow "Попередження! Недупустиме низьке значення затримки програми!\n"

// --- edit decision lists
#define MSGTR_EdlOutOfMem "Не можу виділити достатньо пам'яті для збереження даних EDL.\n"
#define MSGTR_EdlOutOfMemFile "Не можу виділити достатньо пам'яті для зберігання даних EDL імені файлу [%s].\n"
#define MSGTR_EdlRecordsNo "Читання %d EDL дій.\n"
#define MSGTR_EdlQueueEmpty "Немає дій EDL які треба виконати.\n"
#define MSGTR_EdlCantOpenForWrite "Не може відкрити EDL файл [%s] для запису.\n"
#define MSGTR_EdlNOsh_video "Не можу використати EDL без відео, вимикаю.\n"
#define MSGTR_EdlNOValidLine "Невірний рядок EDL: %s\n"
#define MSGTR_EdlBadlyFormattedLine "Погано відформатований EDL рядок [%d], пропускаю.\n"
#define MSGTR_EdlBadLineOverlap "Остання зупинка була [%f]; наступний старт [%f].\n"\
"Записи повинні бути у хронологічному порядку, не можу перекрити. Пропускаю.\n"
#define MSGTR_EdlBadLineBadStop "Час зупинки повинен бути після часу старту.\n"
#define MSGTR_EdloutBadStop "Ігнорування EDL відмінено, останній start > stop\n"
#define MSGTR_EdloutStartSkip "Старт EDL пропуску, натисніть 'i' знов, щоб завершити блок.\n"
#define MSGTR_EdloutEndSkip "Кінець EDL пропуску, рядок записано.\n"

// mplayer.c OSD
#define MSGTR_OSDenabled "увімкнено"
#define MSGTR_OSDdisabled "вимкнено"
#define MSGTR_OSDAudio "Аудіо: %s"
#define MSGTR_OSDChannel "Канал: %s"
#define MSGTR_OSDSubDelay "Затримка субтитрыв: %d мс"
#define MSGTR_OSDSpeed "Швидкість: x %6.2f"
#define MSGTR_OSDosd "OSD: %s"
#define MSGTR_OSDChapter "Розділ: (%d) %s"
#define MSGTR_OSDAngle "Кут: %d/%d"
#define MSGTR_OSDDeinterlace "Деінтерлейс: %s"
#define MSGTR_OSDCapturing "Захоплення: %s"
#define MSGTR_OSDCapturingFailure "Збій захоплення"

// property values
#define MSGTR_Enabled "увімкнено"
#define MSGTR_EnabledEdl "увімкнено (EDL)"
#define MSGTR_Disabled "вимкнено"
#define MSGTR_HardFrameDrop "інтенсивний"
#define MSGTR_Unknown "невідомий"
#define MSGTR_Bottom "низ"
#define MSGTR_Center "центр"
#define MSGTR_Top "верх"
#define MSGTR_SubSourceFile "файл"
#define MSGTR_SubSourceVobsub "vobsub"
#define MSGTR_SubSourceDemux "вкладено"

// OSD bar names
#define MSGTR_Volume "Гучність"
#define MSGTR_Panscan "Зріз сторін"
#define MSGTR_Gamma "Гамма"
#define MSGTR_Brightness "Яскравість"
#define MSGTR_Contrast "Контраст"
#define MSGTR_Saturation "Насиченність"
#define MSGTR_Hue "Відтінок"
#define MSGTR_Balance "Баланс"

// property state
#define MSGTR_LoopStatus "Повтор: %s"
#define MSGTR_MuteStatus "Вимкнути звук: %s"
#define MSGTR_AVDelayStatus "A-V затримка: %s"
#define MSGTR_OnTopStatus "Звурху інших: %s"
#define MSGTR_RootwinStatus "Вікно-root: %s"
#define MSGTR_BorderStatus "Рамка: %s"
#define MSGTR_FramedroppingStatus "Пропуск кадрів: %s"
#define MSGTR_VSyncStatus "Вертикальна синхронізація: %s"
#define MSGTR_SubSelectStatus "Субтитри: %s"
#define MSGTR_SubSourceStatus "Субтитри з: %s"
#define MSGTR_SubPosStatus "Позиція субтитрів: %s/100"
#define MSGTR_SubAlignStatus "Вирівнювання субтитрів: %s"
#define MSGTR_SubDelayStatus "Затримка субтитрів: %s"
#define MSGTR_SubScale "Масштаб субтитрів: %s"
#define MSGTR_SubVisibleStatus "Субтитри: %s"
#define MSGTR_SubForcedOnlyStatus "Форсувати тільки субтитри: %s"

// mencoder.c:
#define MSGTR_UsingPass3ControlFile "Використовую pass3 файл: %s\n"
#define MSGTR_MissingFilename "\nНевизначений файл.\n\n"
#define MSGTR_CannotOpenFile_Device "Неможливо відкрити файл/пристрій.\n"
#define MSGTR_CannotOpenDemuxer "Неможливо відкрити demuxer.\n"
#define MSGTR_NoAudioEncoderSelected "\nНе вибраний аудіо кодек (-oac). Виберіть або використовуйте -nosound. Спробуйте -oac help!\n"
#define MSGTR_NoVideoEncoderSelected "\nНе вибраний відео кодек (-ovc). Виберіть, спробуйте -ovc help!\n"
#define MSGTR_CannotOpenOutputFile "Неможливо створити файл '%s'.\n"
#define MSGTR_EncoderOpenFailed "Неможливо відкрити кодек.\n"
#define MSGTR_MencoderWrongFormatAVI "\nПОПЕРЕДЖЕННЯ: ФОРМАТ ФАЙЛУ НА ВИХОДІ _AVI_. Погляньте -of help.\n"
#define MSGTR_MencoderWrongFormatMPG "\nПОПЕРЕДЖЕННЯ: ФОРМАТ ФАЙЛУ НА ВИХОДІ _MPEG_. Погляньте -of help.\n"
#define MSGTR_MissingOutputFilename "Не вказано файлу на виході, будь-ласка подивіться опцію -o."
#define MSGTR_ForcingOutputFourcc "Встановлюю вихідний fourcc в %x [%.4s]\n"
#define MSGTR_ForcingOutputAudiofmtTag "Форсую таг аудіо фармату на виході до 0x%x.\n"
#define MSGTR_DuplicateFrames "\n%d повторних кадрів!\n"
#define MSGTR_SkipFrame "\nКадр пропущено!\n"
#define MSGTR_ResolutionDoesntMatch "\nНовий та попередній відео файл має різне розширення та кольорову гаму.\n"
#define MSGTR_FrameCopyFileMismatch "\nУсі відео файли повинні мати однакові кадр/сек, розширення, та кодек для -ovc copy.\n"
#define MSGTR_AudioCopyFileMismatch "\nУсі відео файли повинні мати однакові аудіо кодек та формат для -oac copy.\n"
#define MSGTR_NoAudioFileMismatch "\nНе можу поєднати файли відео з файлами аудіо та відео. Спробуйте -nosound.\n"
#define MSGTR_NoSpeedWithFrameCopy "ПОПЕРЕДЖЕННЯ: опція -speed не гарантує коректну роботу з -oac copy!\n"\
"Ваше кодування може бути невдалим!\n"
#define MSGTR_ErrorWritingFile "%s: Помилка запису файлу.\n"
#define MSGTR_FlushingVideoFrames "\nЗкидую кадри відео.\n"
#define MSGTR_FiltersHaveNotBeenConfiguredEmptyFile "Фільтри не було налаштовано! Порожній файл?\n"
#define MSGTR_RecommendedVideoBitrate "Рекомендований бітрейт для %s CD: %d\n"
#define MSGTR_VideoStreamResult "\nВідео потік: %8.3f кбіт/с  (%d Б/с)  розмір: %"PRIu64" байт(ів)  %5.3f сек  %d кадрів\n"
#define MSGTR_AudioStreamResult "\nАудіо потік: %8.3f кбіт/с  (%d Б/с)  розмір: %"PRIu64" байт(ів)  %5.3f сек\n"
#define MSGTR_EdlSkipStartEndCurrent "EDL SKIP: Початок: %.2f  Кінець: %.2f   Поточна: V: %.2f  A: %.2f     \r"
#define MSGTR_OpenedStream "вдало: формат: %d  дані: 0x%X - 0x%x\n"
#define MSGTR_VCodecFramecopy "відеокодек: копія кадрів (%dx%d %dbpp fourcc=%x)\n"
#define MSGTR_ACodecFramecopy "аудіокодек: копія кадрів (формат=%x каналів=%d швидкість=%d бітів=%d Б/с=%d приклад-%d)\n"
#define MSGTR_MP3AudioSelected "Вибрано MP3 аудіо.\n"
#define MSGTR_SettingAudioDelay "Встановлюю аудіо затримку у %5.3fс.\n"
#define MSGTR_SettingVideoDelay "Встановлюю відео затримку у %5.3fс.\n"
#define MSGTR_LimitingAudioPreload "Обмежити підвантаження аудіо до 0.4с.\n"
#define MSGTR_IncreasingAudioDensity "Збільшую густину аудіо до 4.\n"
#define MSGTR_ZeroingAudioPreloadAndMaxPtsCorrection "Форсую аудіо підвантаження до 0, максимальну корекцію pts у 0.\n"
#define MSGTR_LameVersion "Версія LAME %s (%s)\n\n"
#define MSGTR_InvalidBitrateForLamePreset "Помилка: Вказаний бітрейт непидатний для даного встановлення.\n"\
"\n"\
"Використовуючи цей режим ви повинні ввести значення між \"8\" та \"320\".\n"\
"\n"\
"Для подальшої інформації спробуйте: \"-lameopts preset=help\"\n"
#define MSGTR_InvalidLamePresetOptions "Помилка: Ви не ввели придатний профайл та/чи опції з встановлення.\n"\
"\n"\
"Доступні профайли:\n"\
"\n"\
"   <fast>        standard\n"\
"   <fast>        extreme\n"\
"                 insane\n"\
"   <cbr> (Режим ABR) - Мається на увазі режим ABR. Для використання,\n"\
"                       просто вкажіть бітрейт. Наприклад:\n"\
"                       \"preset=185\" активує це\n"\
"                       встановлення та використовує 185 як середнє значення кбіт/с.\n"\
"\n"\
"    Декілька прикладів:\n"\
"\n"\
"    \"-lameopts fast:preset=standard  \"\n"\
" or \"-lameopts  cbr:preset=192       \"\n"\
" or \"-lameopts      preset=172       \"\n"\
" or \"-lameopts      preset=extreme   \"\n"\
"\n"\
"Для подальшої інформації спробуйте: \"-lameopts preset=help\"\n"
#define MSGTR_LamePresetsLongInfo "\n"\
"Встановлення розроблені так, щоб отримати якнайкращу якість.\n"\
"\n"\
"Вони були розроблені та налаштовані у результаті ретельних тестів\n"\
"тести подвійного прослуховування, щоб досягти цього результату.\n"\
"\n"\
"Ключі встановлень постійно поновлюються, щоб відповідати останнім розробленням.\n"\
"в результаті чого ви повинні отримати практично найкращу якість\n"\
"на даний момент можливо при використанні LAME.\n"\
"\n"\
"Щоб активувати ці встановлення:\n"\
"\n"\
"   Для VBR режимів (найкраща якість звичайно):\n"\
"\n"\
"     \"preset=standard\" Звичайно цього встановлення повинно бути достатньо\n"\
"                             для більшості людей та більшості музики, та воно\n"\
"                             являє собою досить високу якість.\n"\
"\n"\
"     \"preset=extreme\" Якщо у вас хороший слух та добра музича апаратура,\n"\
"                             це встановлення як правило забезпечить кращу якість\n"\
"                             ніж режим \"standard\"\n"\
"                             mode.\n"\
"\n"\
"   Для CBR 320kbps (максимально можлива якість, яку можна тримати з встановлень):\n"\
"\n"\
"     \"preset=insane\"  Це встановлення звичайно буде занадто для більшості людей\n"\
"                             та ситуацій, але якщо ви мусите отримати найкращу\n"\
"                             максимально можливу якість, не дивлячись на\n"\
"                             розмір файлу, це ваш вибір.\n"\
"\n"\
"   Для ABR режимів (висока якість для заданого бітрейта, але така висока як VBR):\n"\
"\n"\
"     \"preset=<kbps>\"  Використовуючи це встановлення звичайно дає добру якість\n"\
"                             для заданого бітрейта. Базуючись на введеному\n"\
"                             бітрейті, це встановлення визначить оптимальні\n"\
"                             налаштування для кожной конкретного випадку.\n"\
"                             Не дивлячись на то, що цей підхід працює, він\n"\
"                             далеко не такий гнучкий як VBR, та звичайно не досягає\n"\
"                             такого рівня якості як VBR на високих бітрейтах.\n"\
"\n"\
"Наступні опції також доступні для існуючих профілей:\n"\
"\n"\
"   <fast>        standard\n"\
"   <fast>        extreme\n"\
"                 insane\n"\
"   <cbr> (Режим ABR) - Мається на увазі режим ABR. Для використання\n"\
"                       просто вкажіть бітрейт. Наприклад:\n"\
"                       \"preset=185\" активує це встановлення\n"\
"                       та використая 185 як середнє значення кбіт/сек.\n"\
"\n"\
"   \"fast\" - Вмикає новий швидкий VBR для конкретного профілю.\n"\
"            Недостатком цього ключа є те, що часто бітрейт буде\n"\
"            набагато більше ніж у нормальному режимі;\n"\
"            а якість може буте дещо гірше.\n"\
"Попередження: У теперешній версії швидкі встановлення можуть привести до\n"\
"              високому бітрейту, у порівнянні з звичайними встановленнями.\n"\
"\n"\
"   \"cbr\"  - Якщо ви використовуєте режим ABR (див. вище) з бітрейтом кратним\n"\
"            80, 96, 112, 128, 160, 192, 224, 256, 320,\n"\
"            ви можете застосувати опцію \"cbr\" щоб форсувати кодування у режимі\n"\
"            CBR замість стандартного режиму abr. ABR забезпечує кращу якість,\n"\
"            але CBR може бути корисним у таких ситуаціях,\n"\
"            як передача потоків mp3 через інтернет.\n"\
"\n"\
"    Наприклад:\n"\
"\n"\
"    \"-lameopts fast:preset=standard  \"\n"\
" or \"-lameopts  cbr:preset=192       \"\n"\
" or \"-lameopts      preset=172       \"\n"\
" or \"-lameopts      preset=extreme   \"\n"\
"\n"\
"\n"\
"Декілька псевдонімів доступні для режима ABR:\n"\
"phone => 16kbps/mono        phon+/lw/mw-eu/sw => 24kbps/mono\n"\
"mw-us => 40kbps/mono        voice => 56kbps/mono\n"\
"fm/radio/tape => 112kbps    hifi => 160kbps\n"\
"cd => 192kbps               studio => 256kbps"
#define MSGTR_LameCantInit \
"Не можу встановити опції LAME, перевірте бітрейт/частому_дискретизації, деякі\n"\
"дуже низькі бітрейти (<32) потребують менші частоти\nдискретизації(наприклад, -srate 8000).\n"\
"Якщо все це не допоможе, спробуйте встановлення."
#define MSGTR_ConfigFileError "помилка у файлі налаштувань"
#define MSGTR_ErrorParsingCommandLine "помилка аналізу командного рядка"
#define MSGTR_VideoStreamRequired "Вивід відео обов'язковий!\n"
#define MSGTR_ForcingInputFPS "Вхідні кадри/сек будуть замінені на %5.3f.\n"
#define MSGTR_DemuxerDoesntSupportNosound "Цей демультиплексор поки не підтримується -nosound.\n"
#define MSGTR_MemAllocFailed "Не можу виділити пам'ять.\n"
#define MSGTR_NoMatchingFilter "Не можу знайти потрібний фільтр/формат аудіовиводу!\n"
#define MSGTR_MP3WaveFormatSizeNot30 "sizeof(MPEGLAYER3WAVEFORMAT)==%d!=30, можливо зламаний компілятор C?\n"
#define MSGTR_NoLavcAudioCodecName "Аудіо LAVC, відсутнє назва кодека!\n"
#define MSGTR_LavcAudioCodecNotFound "Аудіо LAVC, не можу знайти кодувальщик для кодека %s.\n"
#define MSGTR_CouldntAllocateLavcContext "Аудіо LAVC, не можу розмістити контекст!\n"
#define MSGTR_CouldntOpenCodec "Не можу відкрити кодек %s, br=%d.\n"
#define MSGTR_CantCopyAudioFormat "Аудіо формат 0x%x не використовується з '-oac copy', спробуйте\n'-oac pcm' замість чи використайте '-fafmttag' для його перевизначення.\n"

// cfg-mencoder.h:
#define MSGTR_MEncoderMP3LameHelp "\n\n"\
" vbr=<0-4>     метод змінного бітрейту\n"\
"                0: cbr (постійний бітрейт)\n"\
"                1: mt (Mark Taylor VBR алгоритм)\n"\
"                2: rh (Robert Hegemann VBR алгоритм - зомовчування)\n"\
"                3: abr (середній бітрейт)\n"\
"                4: mtrh (Mark Taylor Robert Hegemann VBR алгоритм)\n"\
"\n"\
" abr           середній бітрейт\n"\
"\n"\
" cbr           постійний бітрейт\n"\
"               Також форсує CBR режим кодування на слідуючих ABR режимах\n"\
"\n"\
" br=<0-1024>   вказати бітрейт в kBit (тільки для CBR та ABR)\n"\
"\n"\
" q=<0-9>       якість (0-найвища, 9-найнижча) (тільки для VBR)\n"\
"\n"\
" aq=<0-9>      алгорітмична якість (0-краща/повільніша 9-гірша/швидкіша)\n"\
"\n"\
" ratio=<1-100> рівень стиснення\n"\
"\n"\
" vol=<0-10>    встановити посилення вхідного аудіо\n"\
"\n"\
" mode=<0-3>    (замовчування: auto)\n"\
"                0: stereo\n"\
"                1: joint-stereo\n"\
"                2: dualchannel\n"\
"                3: mono\n"\
"\n"\
" padding=<0-2>\n"\
"                0: no\n"\
"                1: all\n"\
"                2: adjust\n"\
"\n"\
" fast          Переходити на швидке кодування при послідовних VBR presets modes,\n"\
"               трохи менша якість та більші бітрейти.\n"\
"\n"\
" preset=<value> запровадити найбільші установки якості.\n"\
"                 середня: VBR кодування, добра якість\n"\
"                 (150-180 kbps бітрейт)\n"\
"                 стандарт: VBR кодування, висока якість\n"\
"                 (170-210 kbps бітрейт)\n"\
"                 висока: VBR кодування, дуже висока якість\n"\
"                 (200-240 kbps бітрейт)\n"\
"                 найкраща: CBR кодування, найвища якость\n"\
"                 (320 kbps бітрейт)\n"\
"                 <8-320>: ABR кодування з вказаним приблизним бітрейтом.\n\n"

// codec-cfg.c
#define MSGTR_DuplicateFourcc "подвоєні FourCC"
#define MSGTR_TooManyFourccs "забагато FourCCs/форматів..."
#define MSGTR_ParseError "помилка у синтаксичному розборі"
#define MSGTR_ParseErrorFIDNotNumber "помилка у синтаксичному розборі (ID формату не є номером?)"
#define MSGTR_ParseErrorFIDAliasNotNumber "помилка у синтаксичному розборі (ID ім'я формату не є номером?)"
#define MSGTR_DuplicateFID "подвоєний ID формату"
#define MSGTR_TooManyOut "забагато вихідних форматів..."
#define MSGTR_InvalidCodecName "\nкодек(%s) ім'я непридатне!\n"
#define MSGTR_CodecLacksFourcc "\nкодек(%s) не має FourCC/фармат!\n"
#define MSGTR_CodecLacksDriver "\nкодек(%s) не має драйверу!\n"
#define MSGTR_CodecNeedsDLL "\nкодек(%s) потребує 'dll'!\n"
#define MSGTR_CodecNeedsOutfmt "\nкодек(%s) потребує 'outfmt'!\n"
#define MSGTR_CantAllocateComment "Не можу виділити пам'ять для коментаря. "
#define MSGTR_GetTokenMaxNotLessThanMAX_NR_TOKEN "get_token(): max >= MAX_MR_TOKEN!"
#define MSGTR_CantGetMemoryForLine "Не можу виділити пам'ять для 'line': %s\n"
#define MSGTR_CantReallocCodecsp "Не можу виконати realloc для '*codecsp': %s\n"
#define MSGTR_CodecNameNotUnique "Назва кодеку '%s' не унікальна."
#define MSGTR_CantStrdupName "Не можу виконати strdup -> 'name': %s\n"
#define MSGTR_CantStrdupInfo "Не можу виконати strdup -> 'info': %s\n"
#define MSGTR_CantStrdupDriver "Не можу виконати strdup -> 'driver': %s\n"
#define MSGTR_CantStrdupDLL "Не можу виконати strdup -> 'dll': %s"
#define MSGTR_AudioVideoCodecTotals "%d аудіо & %d відео кодеки\n"
#define MSGTR_CodecDefinitionIncorrect "Неправильно визначено кодек."
#define MSGTR_OutdatedCodecsConf "Цей codecs.conf застарий та несумісний із цим релізом MPlayer!"

// fifo.c

// parser-mecmd.c, parser-mpcmd.c
#define MSGTR_NoFileGivenOnCommandLine "'--' означає кінець опцій, але не було вказано назви файлу у команд. рядку.\n"
#define MSGTR_TheLoopOptionMustBeAnInteger "Опція loop має бути цілим числом: %s\n"
#define MSGTR_UnknownOptionOnCommandLine "Невідома опція команд. рядку: -%s\n"
#define MSGTR_ErrorParsingOptionOnCommandLine "Помилка аналізу опції команд. рядку: -%s\n"
#define MSGTR_InvalidPlayEntry "Непридатній елемент програвання %s\n"
#define MSGTR_NotAnMEncoderOption "-%s не є опцією MEncoder \n"
#define MSGTR_NoFileGiven "Файл не вказано\n"

// m_config.c
#define MSGTR_SaveSlotTooOld "Знайдений слот збереження застарий з lvl %d: %d !!!\n"
#define MSGTR_InvalidCfgfileOption "Опція %s не може бути використана у файлі конфігурації.\n"
#define MSGTR_InvalidCmdlineOption "Опція %s не може бути використана у команд. рядку.\n"
#define MSGTR_InvalidSuboption "Помилка: опція '%s' не має субопцій '%s'.\n"
#define MSGTR_MissingSuboptionParameter "Помилка: в субопції '%s' опції '%s' повинен бути параметр!\n"
#define MSGTR_MissingOptionParameter "Помилка: опція '%s' повинна мати параметр!\n"
#define MSGTR_OptionListHeader "\n І'мя                 Тип            Мін        Макс      Загальн  CL    Конф\3n\n"
#define MSGTR_TotalOptions "\nЗагалом: %d опцій\n"
#define MSGTR_ProfileInclusionTooDeep "ПОПЕРЕДЖЕННЯ: Включення профайлу дуже глибоко.\n"
#define MSGTR_NoProfileDefined "Не визначено профайлів.\n"
#define MSGTR_AvailableProfiles "Доступні профайлиs:\n"
#define MSGTR_UnknownProfile "Невідомий профайл '%s'.\n"
#define MSGTR_Profile "Профайл %s: %s\n"

// m_property.c
#define MSGTR_PropertyListHeader "\n Назва                 Тип            Мін        Макс\n\n"
#define MSGTR_TotalProperties "\nЗагалом: %d властивостей\n"

// loader/ldt_keeper.c
#define MSGTR_LOADER_DYLD_Warning "ПОПЕРЕДЖЕННЯ: Намагаюсь використати DLL кодеки але змінна середовища\n         DYLD_BIND_AT_LAUNCH не встановлена. Це здається поламка.\n"


// ================================ GUI ================================

#define MSGTR_GUI_AboutMPlayer "Про програму"
#define MSGTR_GUI_Add "Додати"
#define MSGTR_GUI_AspectRatio "Відношення сторін"
#define MSGTR_GUI_Audio "Аудіо"
#define MSGTR_GUI_AudioDelay "Затримка аудіо"
#define MSGTR_GUI_AudioDriverConfiguration "Налаштування аудіо драйверу"
#define MSGTR_GUI_AudioTrack "Завантажити зовнішній аудіо файл"
#define MSGTR_GUI_AudioTracks "Аудіо доріжка"
#define MSGTR_GUI_AvailableDrivers "Доступні драйвери:"
#define MSGTR_GUI_AvailableSkins "Скіни"
#define MSGTR_GUI_Bass "Бас"
#define MSGTR_GUI_Blur "Розпливання"
#define MSGTR_GUI_Bottom "Знизу"
#define MSGTR_GUI_Brightness "Яскравість"
#define MSGTR_GUI_Browse "Дивитись"
#define MSGTR_GUI_Cache "Кеш"
#define MSGTR_GUI_CacheSize "Розмір кешу"
#define MSGTR_GUI_Cancel "Відміна"
#define MSGTR_GUI_Center "Центральний"
#define MSGTR_GUI_Channel1 "Канал 1"
#define MSGTR_GUI_Channel2 "Канал 2"
#define MSGTR_GUI_Channel3 "Канал 3"
#define MSGTR_GUI_Channel4 "Канал 4"
#define MSGTR_GUI_Channel5 "Канал 5"
#define MSGTR_GUI_Channel6 "Канал 6"
#define MSGTR_GUI_ChannelAll "Усі"
#define MSGTR_GUI_ChapterN "Розділ %d"
#define MSGTR_GUI_ChapterNN "Розділ %2d"
#define MSGTR_GUI_Chapters "Розділи"
#define MSGTR_GUI_Clear "Очистити"
#define MSGTR_GUI_CodecFamilyAudio "Драйвер аудіо кодеку"
#define MSGTR_GUI_CodecFamilyVideo "Драйвер відео содеку"
#define MSGTR_GUI_CodecsAndLibraries "Кодеки та сторонні бібліотеки"
#define MSGTR_GUI_Coefficient "Коефіціент"
#define MSGTR_GUI_Configure "Налаштунки"
#define MSGTR_GUI_ConfigureDriver "Налаштувати драйвер"
#define MSGTR_GUI_Contrast "Контраст"
#define MSGTR_GUI_Contributors "Розробники коду та документації"
#define MSGTR_GUI_Cp874 "Thai charset (CP874)"
#define MSGTR_GUI_Cp936 "Simplified Chinese charset (CP936)"
#define MSGTR_GUI_Cp949 "Korean charset (CP949)"
#define MSGTR_GUI_Cp1250 "Slavic/Central European Windows (CP1250)"
#define MSGTR_GUI_Cp1251 "Cyrillic Windows (CP1251)"
#define MSGTR_GUI_Cp1256 "Arabic Windows (CP1256)"
#define MSGTR_GUI_CpBIG5 "Traditional Chinese charset (BIG5)"
#define MSGTR_GUI_CpISO8859_1 "Western European Languages (ISO-8859-1)"
#define MSGTR_GUI_CpISO8859_2 "Slavic/Central European Languages (ISO-8859-2)"
#define MSGTR_GUI_CpISO8859_3 "Esperanto, Galician, Maltese, Turkish (ISO-8859-3)"
#define MSGTR_GUI_CpISO8859_4 "Old Baltic charset (ISO-8859-4)"
#define MSGTR_GUI_CpISO8859_5 "Cyrillic (ISO-8859-5)"
#define MSGTR_GUI_CpISO8859_6 "Arabic (ISO-8859-6)"
#define MSGTR_GUI_CpISO8859_7 "Modern Greek (ISO-8859-7)"
#define MSGTR_GUI_CpISO8859_8 "Hebrew charsets (ISO-8859-8)"
#define MSGTR_GUI_CpISO8859_9 "Turkish (ISO-8859-9)"
#define MSGTR_GUI_CpISO8859_13 "Baltic (ISO-8859-13)"
#define MSGTR_GUI_CpISO8859_14 "Celtic (ISO-8859-14)"
#define MSGTR_GUI_CpISO8859_15 "Western European Languages with Euro (ISO-8859-15)"
#define MSGTR_GUI_CpKOI8_R "Russian (KOI8-R)"
#define MSGTR_GUI_CpKOI8_U "Ukrainian, Belarusian (KOI8-U/RU)"
#define MSGTR_GUI_CpShiftJis "Japanese charsets (SHIFT-JIS)"
#define MSGTR_GUI_CpUnicode "Unicode"
#define MSGTR_GUI_DefaultSetting "звичайний драйвер"
#define MSGTR_GUI_Delay "Затримка"
#define MSGTR_GUI_Demuxers_Codecs "Кодеки й demuxer"
#define MSGTR_GUI_Device "Пристрій"
#define MSGTR_GUI_DeviceCDROM "CD-ROM пристрій"
#define MSGTR_GUI_DeviceDVD "DVD пристрій"
#define MSGTR_GUI_Directory "Шлях"
#define MSGTR_GUI_DirectoryTree "Дерево каталогу"
#define MSGTR_GUI_DropSubtitle "Викинути субтитри..."
#define MSGTR_GUI_DVD "DVD"
#define MSGTR_GUI_EnableAssSubtitle "SSA/ASS вивід субтитрів"
#define MSGTR_GUI_EnableAutomaticAVSync "AutoSync ув/вимк"
#define MSGTR_GUI_EnableCache "Кеш on/off"
#define MSGTR_GUI_EnableDirectRendering "Дозволити прямий вивід"
#define MSGTR_GUI_EnableDoubleBuffering "Дозволити подвійне буферування"
#define MSGTR_GUI_EnableEqualizer "Дозволити еквалайзер"
#define MSGTR_GUI_EnableExtraStereo "Дозволити додаткове стерео"
#define MSGTR_GUI_EnableFrameDropping "Дозволити пропуск кадрів"
#define MSGTR_GUI_EnableFrameDroppingIntense "Дозволити викидування кадрів (небезпечно)"
#define MSGTR_GUI_EnablePlaybar "Дозволити лінійку програвання"
#define MSGTR_GUI_EnablePostProcessing "Дозволити postprocessing"
#define MSGTR_GUI_Encoding "Кодування"
#define MSGTR_GUI_Equalizer "Аквалайзер"
#define MSGTR_GUI_EqualizerConfiguration "Налаштувати Аквалайзер"
#define MSGTR_GUI_Error "Помилка!"
#define MSGTR_GUI_ErrorFatal "Фатальна помилка!"
#define MSGTR_GUI_File "Грати файл"
#define MSGTR_GUI_Files "Файли"
#define MSGTR_GUI_Flip "Перегорнути зображення догори ногами"
#define MSGTR_GUI_Font "Шрифт"
#define MSGTR_GUI_FrameRate "к/c"
#define MSGTR_GUI_FrontLeft "Передній Лівий"
#define MSGTR_GUI_FrontRight "Передній Правий"
#define MSGTR_GUI_HideVideoWindow "Показувати неактивне вікно зображення"
#define MSGTR_GUI_Hue "Тон"
#define MSGTR_GUI_Lavc "Використовувати LAVC (FFmpeg)"
#define MSGTR_GUI_MaximumUsageSpareCPU "Авто якість"
#define MSGTR_GUI_Miscellaneous "Різне"
#define MSGTR_GUI_Mixer "Мікшер"
#define MSGTR_GUI_MixerChannel "Канал мікшеру"
#define MSGTR_GUI_MSG_AddingVideoFilter "[GUI] Додаю відео фільтр: %s\n"
#define MSGTR_GUI_MSG_ColorDepthTooLow "Вибачте, глибина кольору занизька.\n"
#define MSGTR_GUI_MSG_DragAndDropNothing "D&D: Нічого не повернено!\n"
#define MSGTR_GUI_MSG_DXR3NeedsLavc "Вибачте, ви не можете програвати не MPEG файли з вашим DXR3/H+ пристроєм без перекодування.\nВключіть lavc у нашалтунки DXR3/H+."
#define MSGTR_GUI_MSG_LoadingSubtitle "[GUI] Вантажу субтитри: %s\n"
#define MSGTR_GUI_MSG_MemoryErrorImage "Вибачте, не достатньо пам'яті для прорисування буферу.\n"
#define MSGTR_GUI_MSG_MemoryErrorWindow "Вибачте, не достатньо пам'яті для прорисовки буферу."
#define MSGTR_GUI_MSG_NoFileLoaded "Файл не завантажено."
#define MSGTR_GUI_MSG_NoMediaOpened "Носій не відкритий."
#define MSGTR_GUI_MSG_NotAFile0 "Здається, це не файл...\n"
#define MSGTR_GUI_MSG_NotAFile1 "Здається, це не файл: %s !\n"
#define MSGTR_GUI_MSG_PlaybackNeedsRestart "Не забудьте, що вам треба перезапустити програвання для набуття чинності деяких параметрів!"
#define MSGTR_GUI_MSG_RemoteDisplay "Віддалений дисплей, вимикаю XMITSHM.\n"
#define MSGTR_GUI_MSG_RemovingSubtitle "[GUI] Видаляю субтитри.\n"
#define MSGTR_GUI_MSG_SkinBitmapConversionError "помилка конвертування з 24 до 32 біт (%s)\n"
#define MSGTR_GUI_MSG_SkinBitmapNotFound "Файл не знайдено (%s)\n"
#define MSGTR_GUI_MSG_SkinBitmapPngReadError "Помилка читання PNG (%s)\n"
#define MSGTR_GUI_MSG_SkinCfgNotFound "Скін не знайдено (%s).\n"
#define MSGTR_GUI_MSG_SkinCfgSelectedNotFound "Обраний скін ( %s ) не знайдено, обираю 'default'...\n"
#define MSGTR_GUI_MSG_SkinErrorBitmap16Bit "Глибина матриці у 16 біт і менше не підтримується (%s).\n"
#define MSGTR_GUI_MSG_SkinErrorMessage "[скін] помилка у налаштунках скіна у рядку %d: %s"
#define MSGTR_GUI_MSG_SkinFileNotFound "[skin] файл ( %s ) не знайдено.\n"
#define MSGTR_GUI_MSG_SkinFileNotReadable "[skin] файл ( %s ) не прочитати.\n"
#define MSGTR_GUI_MSG_SkinFontFileNotFound "Файл шрифту не знайдено.\n"
#define MSGTR_GUI_MSG_SkinFontImageNotFound "Font image file not found.\n"
#define MSGTR_GUI_MSG_SkinFontNotFound "ідентифікатор шрифту не існує (%s)\n"
#define MSGTR_GUI_MSG_SkinMemoryError "недостатньо пам'яті\n"
#define MSGTR_GUI_MSG_SkinTooManyFonts "Вказано забагато шрифтів.\n"
#define MSGTR_GUI_MSG_SkinUnknownMessage "невідоме повідомлення: %s\n"
#define MSGTR_GUI_MSG_SkinUnknownParameter "невідомий параметр (%s)\n"
#define MSGTR_GUI_MSG_TooManyWindows "Забагато відкритих вікон.\n"
#define MSGTR_GUI_MSG_UnableToSaveOption "[cfg] Не можу зберегти '%s' опцію.\n"
#define MSGTR_GUI_MSG_VideoOutError "Вибачте, не знаходжу відео драйвер для підтримки GUI."
#define MSGTR_GUI_MSG_XShapeError "Вибачте, здається, ваша система не підтримує розширення XShape.\n"
#define MSGTR_GUI_MSG_XSharedMemoryError "помилка розширення загальної пам'яті\n"
#define MSGTR_GUI_MSG_XSharedMemoryUnavailable "Вибачте, ваша система не підтримує розширення загальної пам'яті X.\n"
#define MSGTR_GUI_Mute "Тиша"
#define MSGTR_GUI_NetworkStreaming "Передача потоку..."
#define MSGTR_GUI_Next "Наступний потік"
#define MSGTR_GUI_NoChapter "Без розділу"
#define MSGTR_GUI__none_ "(нема)"
#define MSGTR_GUI_NonInterleavedParser "Використовувати неперемежений AVI парсер"
#define MSGTR_GUI_NormalizeSound "Нормалізувати звук"
#define MSGTR_GUI_Ok "OK"
#define MSGTR_GUI_Open "Відкрити..."
#define MSGTR_GUI_Original "Вихідний"
#define MSGTR_GUI_OsdLevel "Рівень OSD"
#define MSGTR_GUI_OSD_Subtitles "Субтитри й OSD"
#define MSGTR_GUI_Outline "Обведення"
#define MSGTR_GUI_PanAndScan "Panscan"
#define MSGTR_GUI_Pause "Пауза"
#define MSGTR_GUI_Play "Грати"
#define MSGTR_GUI_Playback "Відтворення"
#define MSGTR_GUI_Playlist "Список програвання"
#define MSGTR_GUI_Position "Положення"
#define MSGTR_GUI_PostProcessing "Postprocessing"
#define MSGTR_GUI_Preferences "Hалаштування"
#define MSGTR_GUI_Previous "Попередній потік"
#define MSGTR_GUI_Quit "Вихід"
#define MSGTR_GUI_RearLeft "Задній Лівий"
#define MSGTR_GUI_RearRight "Задній Правий"
#define MSGTR_GUI_Remove "Видалити"
#define MSGTR_GUI_Saturation "Насиченість"
#define MSGTR_GUI_SaveWindowPositions "Зберігати положення вікна"
#define MSGTR_GUI_ScaleMovieDiagonal "Пропорційно діагоналі кадру"
#define MSGTR_GUI_ScaleMovieHeight "Пропорційно висоті кадру"
#define MSGTR_GUI_ScaleMovieWidth "Пропорційно ширині кадру"
#define MSGTR_GUI_ScaleNo "Без автомасштабування"
#define MSGTR_GUI_SeekingInBrokenMedia "Перебудувати індекс, якщо треба"
#define MSGTR_GUI_SelectAudioFile "Вибрати іншу аудіо доріжку..."
#define MSGTR_GUI_SelectedFiles "Вибрані файли"
#define MSGTR_GUI_SelectFile "Вибрати файл..."
#define MSGTR_GUI_SelectFont "Вибрати шрифт..."
#define MSGTR_GUI_SelectSubtitle "Вибрати субтитри..."
#define MSGTR_GUI_SizeDouble "Подвійний розмір"
#define MSGTR_GUI_SizeFullscreen "Повний екран"
#define MSGTR_GUI_SizeHalf "Half size"
#define MSGTR_GUI_SizeNormal "Нормальний розмір"
#define MSGTR_GUI_SizeOSD "Масштаб OSD"
#define MSGTR_GUI_SizeSubtitles "Масштаб тексту"
#define MSGTR_GUI_SkinBrowser "Переглядач жупанів"
#define MSGTR_GUI_Skins "Жупани"
#define MSGTR_GUI_Sponsored "GUI розробку спонсовано UHU Linux"
#define MSGTR_GUI_StartFullscreen "Стартувати в полний екран"
#define MSGTR_GUI_Stop "Зупинити"
#define MSGTR_GUI_Subtitle "Субтитри"
#define MSGTR_GUI_SubtitleAddMargins "Використовувати кордони"
#define MSGTR_GUI_SubtitleAllowOverlap "Дозволити/заборонити перекриття субтитрів"
#define MSGTR_GUI_SubtitleAutomaticLoad "Заборонити автозавантаження субтитрів"
#define MSGTR_GUI_SubtitleConvertMpsub "Перетворити вказані субтитри до формату MPlayer"
#define MSGTR_GUI_SubtitleConvertSrt "Перетворити вказані субтитри до формату SubViewer (SRT)"
#define MSGTR_GUI_Subtitles "Субтитри"
#define MSGTR_GUI_SyncValue "Autosync"
#define MSGTR_GUI_TitleNN "Титр %2d"
#define MSGTR_GUI_Titles "Титри"
#define MSGTR_GUI_Top "Угорі"
#define MSGTR_GUI_TrackN "Доріжка %d"
#define MSGTR_GUI_Translations "Переклади"
#define MSGTR_GUI_TurnOffXScreenSaver "Зупинити XScreenSaver"
#define MSGTR_GUI_URL "Грати URL"
#define MSGTR_GUI_VCD "VCD"
#define MSGTR_GUI_Video "Відео"
#define MSGTR_GUI_VideoEncoder "Відео кодек"
#define MSGTR_GUI_VideoTracks "Відео доріжка"
#define MSGTR_GUI_Warning "Попередження!"

// Win32 GUI
#define MSGTR_Close "Закрити"
#define MSGTR_Default "Типові значення"
#define MSGTR_Down "Вниз"
#define MSGTR_Load "Завантажити"
#define MSGTR_Save "Зберегти"
#define MSGTR_Up "Вгору"
#define MSGTR_DirectorySelect "Вибрати каталог..."
#define MSGTR_PlaylistSave "Зберегти список програвання..."
#define MSGTR_PlaylistSelect "Вибрати список програвання..."
#define MSGTR_SelectTitleChapter "Вибрати ролик/разділ..."
#define MSGTR_MENU_DebugConsole "Консоль зневадження"
#define MSGTR_MENU_OnlineHelp "Онлайн довідка"
#define MSGTR_MENU_PlayDirectory "Програти каталог..."
#define MSGTR_MENU_SeekBack "Перейти назад"
#define MSGTR_MENU_SeekForw "Перейти вперед"
#define MSGTR_MENU_ShowHide "Показати/Сховати"
#define MSGTR_MENU_SubtitlesOnOff "Видимість субтитрів вкл./выкл."
#define MSGTR_PLAYLIST_AddFile "Додати файл..."
#define MSGTR_PLAYLIST_AddURL "Додати URL..."
#define MSGTR_PREFERENCES_Priority "Приорітет:"
#define MSGTR_PREFERENCES_PriorityHigh "високий"
#define MSGTR_PREFERENCES_PriorityLow "низький"
#define MSGTR_PREFERENCES_PriorityNormal "звичайний"
#define MSGTR_PREFERENCES_PriorityNormalAbove "вище звичайного"
#define MSGTR_PREFERENCES_PriorityNormalBelow "нижче звичайного"
#define MSGTR_PREFERENCES_ShowInVideoWin "Показати у вікні відео (тільки DirectX)"


// ======================= video output drivers ========================

#define MSGTR_VOincompCodec "Обраний пристрій виводу відео несумісний з цим кодеком.\n"\
                "Спробуйте додати фільтр scale до списку вашого списку фільтрів,\n"\
                "наприклад. -vf spp,scale замість -vf spp.\n"
#define MSGTR_VO_GenericError "Виникла слідуюча помилка"
#define MSGTR_VO_UnableToAccess "Неможлово отримати доступ"
#define MSGTR_VO_ExistsButNoDirectory "вже існує, але це не директорія."
#define MSGTR_VO_DirExistsButNotWritable "Директорія виводу вже існує, але не доступна для запису."
#define MSGTR_VO_CantCreateDirectory "Не можу створити директорію виводу."
#define MSGTR_VO_CantCreateFile "Не можу створити файл виводу."
#define MSGTR_VO_DirectoryCreateSuccess "Директорія виводу успішно створена."
#define MSGTR_VO_ValueOutOfRange "значення за межами доступного діапазону"

// aspect.c
#define MSGTR_LIBVO_ASPECT_NoSuitableNewResFound "[ASPECT] Попередження: Не знайдено потрібного розширення!\n"
#define MSGTR_LIBVO_ASPECT_NoNewSizeFoundThatFitsIntoRes "[ASPECT] Помилка: Не знайдено розмір, що помістився б у дане розширення!\n"

// font_load_ft.c
#define MSGTR_LIBVO_FONT_LOAD_FT_NewFaceFailed "Помилка New_Face. Можливо шлях до шрифту невірний.\nВкажіть файл шрифту (~/.mplayer/subfont.ttf).\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_NewMemoryFaceFailed "Помилка New_Memory_Face..\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_SubFaceFailed "шрифт субтитрів: помилка load_sub_face.\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_SubFontCharsetFailed "шрифт субтитрів: помилка prepare_charset.\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_CannotPrepareSubtitleFont "Не можу підготувати шрифт субтитрів.\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_CannotPrepareOSDFont "Не можу підготувати шрифт OSD.\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_CannotGenerateTables "Не можу генерувати таблиці.\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_DoneFreeTypeFailed "Помилка FT_Done_FreeType.\n"
#define MSGTR_LIBVO_FONT_LOAD_FT_FontconfigNoMatch "Збій fontconfig при виборі шрифта. Спробуйте без fontconfig...\n"

// sub.c
#define MSGTR_VO_SUB_Seekbar "Навігація"
#define MSGTR_VO_SUB_Play "Грати"
#define MSGTR_VO_SUB_Pause "Пауза"
#define MSGTR_VO_SUB_Stop "Стоп"
#define MSGTR_VO_SUB_Rewind "Назад"
#define MSGTR_VO_SUB_Forward "Уперед"
#define MSGTR_VO_SUB_Clock "Час"
#define MSGTR_VO_SUB_Contrast "Контраст"
#define MSGTR_VO_SUB_Saturation "Насиченість"
#define MSGTR_VO_SUB_Volume "Гучність"
#define MSGTR_VO_SUB_Brightness "Блискучість"
#define MSGTR_VO_SUB_Hue "Колір"
#define MSGTR_VO_SUB_Balance "Баланс"

// vo_3dfx.c
#define MSGTR_LIBVO_3DFX_Only16BppSupported "[VO_3DFX] Підтримується тільки 16bpp!"
#define MSGTR_LIBVO_3DFX_VisualIdIs "[VO_3DFX] Візуальний ID  %lx.\n"
#define MSGTR_LIBVO_3DFX_UnableToOpenDevice "[VO_3DFX] Не можу відкрити /dev/3dfx.\n"
#define MSGTR_LIBVO_3DFX_Error "[VO_3DFX] Помилка: %d.\n"
#define MSGTR_LIBVO_3DFX_CouldntMapMemoryArea "[VO_3DFX] Не можу показати області пам'яті 3dfx: %p,%p,%d.\n"
#define MSGTR_LIBVO_3DFX_DisplayInitialized "[VO_3DFX] Ініціалізовано: %p.\n"
#define MSGTR_LIBVO_3DFX_UnknownSubdevice "[VO_3DFX] Невідомий підпристрій: %s.\n"

// vo_aa.c
#define MSGTR_VO_AA_HelpHeader "\n\nСубопції vo_aa бібліотеки aalib:\n"
#define MSGTR_VO_AA_AdditionalOptions "Додаткові опції, що забезпечує vo_aa:\n" \
"  help        показати це повідомлення\n" \
"  osdcolor    встановити колір OSD\n  subcolor    встановити колір субтитрівr\n" \
"        параметри кольору:\n           0 : стандартний\n" \
"           1 : дим\n           2 : товстий\n           3 : товстий шрифт\n" \
"           4 : реверс\n           5 : спеціяльний\n\n\n"


// vo_dxr3.c
#define MSGTR_LIBVO_DXR3_UnableToLoadNewSPUPalette "[VO_DXR3] Не можу завантажити нову палітру SPU!\n"
#define MSGTR_LIBVO_DXR3_UnableToSetPlaymode "[VO_DXR3] Не можу встановити режим програвання!\n"
#define MSGTR_LIBVO_DXR3_UnableToSetSubpictureMode "[VO_DXR3] Не можу встановити режим субкартинки!\n"
#define MSGTR_LIBVO_DXR3_UnableToGetTVNorm "[VO_DXR3] Не можу отримати режим ТБ!\n"
#define MSGTR_LIBVO_DXR3_AutoSelectedTVNormByFrameRate "[VO_DXR3] Авто-вибір режиму ТБ за частотою кадрів: "
#define MSGTR_LIBVO_DXR3_UnableToSetTVNorm "[VO_DXR3] Не можу отримати режим ТБ!\n"
#define MSGTR_LIBVO_DXR3_SettingUpForNTSC "[VO_DXR3] Встановлюю для NTSC.\n"
#define MSGTR_LIBVO_DXR3_SettingUpForPALSECAM "[VO_DXR3] Встановлюю для PAL/SECAM.\n"
#define MSGTR_LIBVO_DXR3_SettingAspectRatioTo43 "[VO_DXR3] Встановлюю пропорції 4:3.\n"
#define MSGTR_LIBVO_DXR3_SettingAspectRatioTo169 "[VO_DXR3] Встановлюю пропорції 16:9.\n"
#define MSGTR_LIBVO_DXR3_OutOfMemory "[VO_DXR3] не вистачає пам'яті\n"
#define MSGTR_LIBVO_DXR3_UnableToAllocateKeycolor "[VO_DXR3] Не можу знайти головний колір!\n"
#define MSGTR_LIBVO_DXR3_UnableToAllocateExactKeycolor "[VO_DXR3] Не можу знайти точний головний колір, використовую найбільш схоже (0x%lx).\n"
#define MSGTR_LIBVO_DXR3_Uninitializing "[VO_DXR3] Ініціялізування.\n"
#define MSGTR_LIBVO_DXR3_FailedRestoringTVNorm "[VO_DXR3] Не можу встановити режим ТБ!\n"
#define MSGTR_LIBVO_DXR3_EnablingPrebuffering "[VO_DXR3] Дозволяю попередню буферизацію.\n"
#define MSGTR_LIBVO_DXR3_UsingNewSyncEngine "[VO_DXR3] Використовую новий механізм синхронізації.\n"
#define MSGTR_LIBVO_DXR3_UsingOverlay "[VO_DXR3] Використовую оверлей.\n"
#define MSGTR_LIBVO_DXR3_ErrorYouNeedToCompileMplayerWithX11 "[VO_DXR3] Помилка: Оверлей потребує збирання з встановленими бібліотеками/допоміжними файлами X11.\n"
#define MSGTR_LIBVO_DXR3_WillSetTVNormTo "[VO_DXR3] Встановлюю режим ТБ у: "
#define MSGTR_LIBVO_DXR3_AutoAdjustToMovieFrameRatePALPAL60 "авто-регулювання за частотою кадрів фільма (PAL/PAL-60)"
#define MSGTR_LIBVO_DXR3_AutoAdjustToMovieFrameRatePALNTSC "авто-регулювання за частотою кадрів фільма (PAL/NTSC)"
#define MSGTR_LIBVO_DXR3_UseCurrentNorm "Використовую поточний режим."
#define MSGTR_LIBVO_DXR3_UseUnknownNormSuppliedCurrentNorm "Запропонований невідомий режим. Спробуйте поточний."
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingTrying "[VO_DXR3] Помилка при відкритті %s для запису, пробую /dev/em8300 замість.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingTryingMV "[VO_DXR3] Помилка при відкритті %s для запису, пробую /dev/em8300_mv замість.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingAsWell "[VO_DXR3] Також помилка при відкритті /dev/em8300 для запису!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingAsWellMV "[VO_DXR3] Також помилка при відкритті /dev/em8300_для запису!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_Opened "[VO_DXR3] Відкрито: %s.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingTryingSP "[VO_DXR3] Помилка при відкритті %s для запису, пробую /dev/em8300_sp замість.\n"
#define MSGTR_LIBVO_DXR3_ErrorOpeningForWritingAsWellSP "[VO_DXR3] Також помилка при відкритті /dev/em8300_sp для запису!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_UnableToOpenDisplayDuringHackSetup "[VO_DXR3] Не можу відкрити дисплей у час встановлення хаку оверлея!\n"
#define MSGTR_LIBVO_DXR3_UnableToInitX11 "[VO_DXR3] Не можу ініціялізувати X11!\n"
#define MSGTR_LIBVO_DXR3_FailedSettingOverlayAttribute "[VO_DXR3] Невдалось встановити атрибут оверлея.\n"
#define MSGTR_LIBVO_DXR3_FailedSettingOverlayScreen "[VO_DXR3] Невдалось встановити екран оверлею!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_FailedEnablingOverlay "[VO_DXR3] Неадалось увімкнути оверлей!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_FailedResizingOverlayWindow "[VO_DXR3] Невдалось зімнити розмір вікна оверлею!\n"
#define MSGTR_LIBVO_DXR3_FailedSettingOverlayBcs "[VO_DXR3] Невдалося встановити bcs оверлею!\n"
#define MSGTR_LIBVO_DXR3_FailedGettingOverlayYOffsetValues "[VO_DXR3] Не можу отримати значення Y-зміщення оверлею!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_FailedGettingOverlayXOffsetValues "[VO_DXR3] Не можу отримати значення X-зміщення оверлею!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_FailedGettingOverlayXScaleCorrection "[VO_DXR3] Не можу отримати корекцію оверлея масштабування X!\nВиходжу.\n"
#define MSGTR_LIBVO_DXR3_YOffset "[VO_DXR3] Зміщення за Y: %d.\n"
#define MSGTR_LIBVO_DXR3_XOffset "[VO_DXR3] Зміщення за X: %d.\n"
#define MSGTR_LIBVO_DXR3_XCorrection "[VO_DXR3] Корекція за X: %d.\n"
#define MSGTR_LIBVO_DXR3_FailedSetSignalMix "[VO_DXR3] Не можу встановити сигнал mix!\n"

// vo_jpeg.c
#define MSGTR_VO_JPEG_ProgressiveJPEG "Увімкнено прогресивний JPEG."
#define MSGTR_VO_JPEG_NoProgressiveJPEG "Ввимкнено прогресивний JPEG."
#define MSGTR_VO_JPEG_BaselineJPEG "Увімкнено основний JPEG."
#define MSGTR_VO_JPEG_NoBaselineJPEG "Ввимкнено основний JPEG."

// vo_mga.c
#define MSGTR_LIBVO_MGA_AspectResized "[VO_MGA] aspect(): розмір змінений до %dx%d.\n"
#define MSGTR_LIBVO_MGA_Uninit "[VO] деініціялізація!\n"

// mga_template.c
#define MSGTR_LIBVO_MGA_ErrorInConfigIoctl "[MGA] помилка у mga_vid_config ioctl (неправильна версія mga_vid.o?)"
#define MSGTR_LIBVO_MGA_CouldNotGetLumaValuesFromTheKernelModule "[MGA] Не можу отримати значення luma з модуля ядра!\n"
#define MSGTR_LIBVO_MGA_CouldNotSetLumaValuesFromTheKernelModule "[MGA] Не можу встановити значення luma з модуля ядра!\n"
#define MSGTR_LIBVO_MGA_ScreenWidthHeightUnknown "[MGA] Невідома ширина/висота екрану!\n"
#define MSGTR_LIBVO_MGA_InvalidOutputFormat "[MGA] непридатний вихідний формат %0X\n"
#define MSGTR_LIBVO_MGA_IncompatibleDriverVersion "[MGA] Версія вашого mga_vid драйверу несумісна із цією версією MPlayer!\n"
#define MSGTR_LIBVO_MGA_CouldntOpen "[MGA] Не можу відкрити: %s\n"
#define MSGTR_LIBVO_MGA_ResolutionTooHigh "[MGA] Розширення джерела, у крайньому випадку в одному вимірі, більше ніж 1023x1023.\n[MGA] Перемасштабуйте програмно або викорстайте -lavdopts lowres=1.\n"
#define MSGTR_LIBVO_MGA_mgavidVersionMismatch "[MGA] версія драйверу mga_vid ядра (%u) та MPlayer (%u) не співпадають\n"

// vo_null.c
#define MSGTR_LIBVO_NULL_UnknownSubdevice "[VO_NULL] Невідомий підпристрій: %s.\n"

// vo_png.c
#define MSGTR_LIBVO_PNG_Warning1 "[VO_PNG] Попередження: рівень стиснення встановлено 0, стиснення вимкнено!\n"
#define MSGTR_LIBVO_PNG_Warning2 "[VO_PNG] Інфо: Використайте -vo png:z=<n> щоб встановити рівень стиснення з 0 до 9.\n"
#define MSGTR_LIBVO_PNG_Warning3 "[VO_PNG] Інфо: (0 = без стиснення, 1 = найшвидша, найповільніша - 9 але найкраще стиснення)\n"
#define MSGTR_LIBVO_PNG_ErrorOpeningForWriting "\n[VO_PNG] Помилка при відкритті '%s' для запису!\n"
#define MSGTR_LIBVO_PNG_ErrorInCreatePng "[VO_PNG] Помилка при створенні png.\n"

// vo_pnm.c
#define MSGTR_VO_PNM_ASCIIMode "Режим ASCII увімкнено."
#define MSGTR_VO_PNM_RawMode "Режим Raw увімкнено."
#define MSGTR_VO_PNM_PPMType "Запише файли PPM."
#define MSGTR_VO_PNM_PGMType "Запише файли PGM."
#define MSGTR_VO_PNM_PGMYUVType "Запише файли PGMYUV."

// vo_sdl.c
#define MSGTR_LIBVO_SDL_CouldntGetAnyAcceptableSDLModeForOutput "[VO_SDL] Не можу вивести прийнятний SDL Mode.\n"
#define MSGTR_LIBVO_SDL_UnsupportedImageFormat "[VO_SDL] Формат картинки не підтримується (0x%X).\n"
#define MSGTR_LIBVO_SDL_InfoPleaseUseVmOrZoom "[VO_SDL] Інфо - спробуйте -vm чи -zoom щоб перейти до найкращої роздільної здатності.\n"
#define MSGTR_LIBVO_SDL_FailedToSetVideoMode "[VO_SDL] Не вдалося встановити відео режим: %s.\n"
#define MSGTR_LIBVO_SDL_CouldntCreateAYUVOverlay "[VO_SDL] Не вдалося створити оверлей YUV: %s.\n"
#define MSGTR_LIBVO_SDL_CouldntCreateARGBSurface "[VO_SDL] Не вдалося створити поверхню RGB: %s.\n"
#define MSGTR_LIBVO_SDL_UsingDepthColorspaceConversion "[VO_SDL] Використовую перетворення глибини/кольорового простору, це уповільнить протікання процесу (%ibpp -> %ibpp).\n"
#define MSGTR_LIBVO_SDL_UnsupportedImageFormatInDrawslice "[VO_SDL] Формат картинки не підтримується у draw_slice, повідомте розробників MPlayer!\n"
#define MSGTR_LIBVO_SDL_BlitFailed "[VO_SDL] Збій Blit: %s.\n"
#define MSGTR_LIBVO_SDL_InitializationFailed "[VO_SDL] Ініціялізація SDL не вдалася: %s.\n"
#define MSGTR_LIBVO_SDL_UsingDriver "[VO_SDL] Використовую драйвер: %s.\n"

// vo_svga.c
#define MSGTR_LIBVO_SVGA_ForcedVidmodeNotAvailable "[VO_SVGA] Форсований vid_mode %d (%s) не доступний.\n"
#define MSGTR_LIBVO_SVGA_ForcedVidmodeTooSmall "[VO_SVGA] Форсований vid_mode %d (%s) замалий.\n"
#define MSGTR_LIBVO_SVGA_Vidmode "[VO_SVGA] Vid_mode: %d, %dx%d %dbpp.\n"
#define MSGTR_LIBVO_SVGA_VgasetmodeFailed "[VO_SVGA] Збій Vga_setmode(%d).\n"
#define MSGTR_LIBVO_SVGA_VideoModeIsLinearAndMemcpyCouldBeUsed "[VO_SVGA] Режим Відео лінійний та для передачі зображення може бути\nвикористаний memcpy.\n"
#define MSGTR_LIBVO_SVGA_VideoModeHasHardwareAcceleration "[VO_SVGA] Режим Відео має апаратне прискорення тому може бути кокористаний put_image.\n"
#define MSGTR_LIBVO_SVGA_IfItWorksForYouIWouldLikeToKnow "[VO_SVGA] Якщо це працює у вас, дайте мені знати.\n[VO_SVGA] (надішліть лоґ з `mplayer test.avi -v -v -v -v &> svga.log`). Дякую!\n"
#define MSGTR_LIBVO_SVGA_VideoModeHas "[VO_SVGA] Режим Відео має %d сторінку(ок/ки).\n"
#define MSGTR_LIBVO_SVGA_CenteringImageStartAt "[VO_SVGA] Centering image. Starting at (%d,%d)\n"
#define MSGTR_LIBVO_SVGA_UsingVidix "[VO_SVGA] Використовую VIDIX. w=%i h=%i  mw=%i mh=%i\n"

// vo_tdfx_vid.c
#define MSGTR_LIBVO_TDFXVID_Move "[VO_TDXVID] Переміщую %d(%d) x %d => %d.\n"
#define MSGTR_LIBVO_TDFXVID_AGPMoveFailedToClearTheScreen "[VO_TDFXVID] Переміщення AGP не вдалося очистити екран.\n"
#define MSGTR_LIBVO_TDFXVID_BlitFailed "[VO_TDFXVID] Збій Blit.\n"
#define MSGTR_LIBVO_TDFXVID_NonNativeOverlayFormatNeedConversion "[VO_TDFXVID] Нестандартний формат оверлею потребує перетворення.\n"
#define MSGTR_LIBVO_TDFXVID_UnsupportedInputFormat "[VO_TDFXVID] Формат вводу 0x%x не підтримується.\n"
#define MSGTR_LIBVO_TDFXVID_OverlaySetupFailed "[VO_TDFXVID] Встановлення оверлею не вдалося.\n"
#define MSGTR_LIBVO_TDFXVID_OverlayOnFailed "[VO_TDFXVID] Помилка оверлею.\n"
#define MSGTR_LIBVO_TDFXVID_OverlayReady "[VO_TDFXVID] Оверлей готовий: %d(%d) x %d @ %d => %d(%d) x %d @ %d.\n"
#define MSGTR_LIBVO_TDFXVID_TextureBlitReady "[VO_TDFXVID] Blit текстур готовий: %d(%d) x %d @ %d => %d(%d) x %d @ %d.\n"
#define MSGTR_LIBVO_TDFXVID_OverlayOffFailed "[VO_TDFXVID] Ввимкнення оверлею не вдолося\n"
#define MSGTR_LIBVO_TDFXVID_CantOpen "[VO_TDFXVID] Не можу відкрити %s: %s.\n"
#define MSGTR_LIBVO_TDFXVID_CantGetCurrentCfg "[VO_TDFXVID] Не можу отримати поточну конфігурацію: %s.\n"
#define MSGTR_LIBVO_TDFXVID_MemmapFailed "[VO_TDFXVID] Збій memmap !!!!!\n"
#define MSGTR_LIBVO_TDFXVID_GetImageTodo "Треба доробити картинку.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailed "[VO_TDFXVID] Переміщення AGP не вдалося.\n"
#define MSGTR_LIBVO_TDFXVID_SetYuvFailed "[VO_TDFXVID] Встановлення YUV не вдалося.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailedOnYPlane "[VO_TDFXVID] Переміщення AGP не вдалося на проєкції Y.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailedOnUPlane "[VO_TDFXVID] Переміщення AGP не вдалося на проєкції U.\n"
#define MSGTR_LIBVO_TDFXVID_AgpMoveFailedOnVPlane "[VO_TDFXVID] Переміщення AGP не вдалося на проєкції V.\n"
#define MSGTR_LIBVO_TDFXVID_UnknownFormat "[VO_TDFXVID] невідомий формат: 0x%x.\n"

// vo_tdfxfb.c
#define MSGTR_LIBVO_TDFXFB_CantOpen "[VO_TDFXFB] Не можу відкрити %s: %s.\n"
#define MSGTR_LIBVO_TDFXFB_ProblemWithFbitgetFscreenInfo "[VO_TDFXFB] Проблема з FBITGET_FSCREENINFO ioctl: %s.\n"
#define MSGTR_LIBVO_TDFXFB_ProblemWithFbitgetVscreenInfo "[VO_TDFXFB] Проблема з FBITGET_VSCREENINFO ioctl: %s.\n"
#define MSGTR_LIBVO_TDFXFB_ThisDriverOnlySupports "[VO_TDFXFB] Це драйвер підтримує тільки 3Dfx Banshee, Voodoo3 та Voodoo 5.\n"
#define MSGTR_LIBVO_TDFXFB_OutputIsNotSupported "[VO_TDFXFB] %d вивід bpp не підтримується.\n"
#define MSGTR_LIBVO_TDFXFB_CouldntMapMemoryAreas "[VO_TDFXFB] Не можу показати частини пам'яті: %s.\n"
#define MSGTR_LIBVO_TDFXFB_BppOutputIsNotSupported "[VO_TDFXFB] %d вивід bpp не підтримується (Цього зовсім не повинно траплятися).\n"
#define MSGTR_LIBVO_TDFXFB_SomethingIsWrongWithControl "[VO_TDFXFB] Ой! Щось сталося з control().\n"
#define MSGTR_LIBVO_TDFXFB_NotEnoughVideoMemoryToPlay "[VO_TDFXFB] Не достатньо пам'яті щоб програти це відео. Спробуйте меншу роздільну здатність.\n"
#define MSGTR_LIBVO_TDFXFB_ScreenIs "[VO_TDFXFB] Екран %dx%d на %d bpp, у %dx%d на %d bpp, режим %dx%d.\n"

// vo_tga.c
#define MSGTR_LIBVO_TGA_UnknownSubdevice "[VO_TGA] Невідомий підпристрій: %s.\n"

// vo_vesa.c
#define MSGTR_LIBVO_VESA_FatalErrorOccurred "[VO_VESA] Виникла фатально помилка! Не можу продовжити.\n"
#define MSGTR_LIBVO_VESA_UnknownSubdevice "[VO_VESA] невідомий підпристрій: '%s'.\n"
#define MSGTR_LIBVO_VESA_YouHaveTooLittleVideoMemory "[VO_VESA] Замало відео пам'яті для цього режиму:\n[VO_VESA] Потребує: %08lX є: %08lX.\n"
#define MSGTR_LIBVO_VESA_YouHaveToSpecifyTheCapabilitiesOfTheMonitor "[VO_VESA] Ви маєте вказати можливості монітора. Не змінюю частому оновлення.\n"
#define MSGTR_LIBVO_VESA_UnableToFitTheMode "[VO_VESA] Режим не відповідає обмеженням монітора. Не змінюю частому оновлення.\n"
#define MSGTR_LIBVO_VESA_DetectedInternalFatalError "[VO_VESA] Виявлена фатальна внутрішня помилка: init викликаний перед preinit.\n"
#define MSGTR_LIBVO_VESA_SwitchFlipIsNotSupported "[VO_VESA] Опція -flip не підтримується.\n"
#define MSGTR_LIBVO_VESA_PossibleReasonNoVbe2BiosFound "[VO_VESA] Можлива причина: Не знайдено VBE2 BIOS.\n"
#define MSGTR_LIBVO_VESA_FoundVesaVbeBiosVersion "[VO_VESA] Знайдено VESA VBE BIOS, версія %x.%x ревізія: %x.\n"
#define MSGTR_LIBVO_VESA_VideoMemory "[VO_VESA] Відео пам'ять: %u Кб.\n"
#define MSGTR_LIBVO_VESA_Capabilites "[VO_VESA] Можливості VESA: %s %s %s %s %s.\n"
#define MSGTR_LIBVO_VESA_BelowWillBePrintedOemInfo "[VO_VESA] !!! OEM інформація буде виведена нище !!!\n"
#define MSGTR_LIBVO_VESA_YouShouldSee5OemRelatedLines "[VO_VESA] Ви повинні бачити 5 рядків інфо про OEM нище; Якщо ні, у вас поламана vm86.\n"
#define MSGTR_LIBVO_VESA_OemInfo "[VO_VESA] OEM інфо: %s.\n"
#define MSGTR_LIBVO_VESA_OemRevision "[VO_VESA] OEM ревізія: %x.\n"
#define MSGTR_LIBVO_VESA_OemVendor "[VO_VESA] OEM постачальник: %s.\n"
#define MSGTR_LIBVO_VESA_OemProductName "[VO_VESA] Назва продукту OEM: %s.\n"
#define MSGTR_LIBVO_VESA_OemProductRev "[VO_VESA] Ревізія продукту OEM: %s.\n"
#define MSGTR_LIBVO_VESA_Hint "[VO_VESA] Підказка: Для роботи ТБ-виходу вам необхідно підключити ТБ роз'єм\n"\
"[VO_VESA] перед завантаженням як VESA BIOS ініціялізує себе протягом POST.\n"
#define MSGTR_LIBVO_VESA_UsingVesaMode "[VO_VESA] Використовую режим VESA (%u) = %x [%ux%u@%u]\n"
#define MSGTR_LIBVO_VESA_CantInitializeSwscaler "[VO_VESA] Не можу ініціялізувати програмне масштабування.\n"
#define MSGTR_LIBVO_VESA_CantUseDga "[VO_VESA] Не можу використовувати DGA. Форсую режим комутації сегментів. :(\n"
#define MSGTR_LIBVO_VESA_UsingDga "[VO_VESA] Використовую DGA (фізичні ресурси: %08lXh, %08lXh)"
#define MSGTR_LIBVO_VESA_CantUseDoubleBuffering "[VO_VESA] Не можу використати подвійну буферизацію: не достатньо відео пам'яті.\n"
#define MSGTR_LIBVO_VESA_CantFindNeitherDga "[VO_VESA] Не можу знайти ні DGA ні переміщуваного фрейму вікна.\n"
#define MSGTR_LIBVO_VESA_YouveForcedDga "[VO_VESA] Ви форсували DGA. Виходжу\n"
#define MSGTR_LIBVO_VESA_CantFindValidWindowAddress "[VO_VESA] Не можу знайти правильну адресу вікна.\n"
#define MSGTR_LIBVO_VESA_UsingBankSwitchingMode "[VO_VESA] Використовую режим комутації сегментів (фізичні ресурси: %08lXh, %08lXh).\n"
#define MSGTR_LIBVO_VESA_CantAllocateTemporaryBuffer "[VO_VESA] Не можу виділити тимчасовий буфер.\n"
#define MSGTR_LIBVO_VESA_SorryUnsupportedMode "[VO_VESA] Вибачте, режим не підтримується -- спробуйте -x 640 -zoom.\n"
#define MSGTR_LIBVO_VESA_OhYouReallyHavePictureOnTv "[VO_VESA] О, ви справді маєте картинку на ТБ!\n"
#define MSGTR_LIBVO_VESA_CantInitialozeLinuxVideoOverlay "[VO_VESA] Не можу ініціялізувати Відео оверлей Linux.\n"
#define MSGTR_LIBVO_VESA_UsingVideoOverlay "[VO_VESA] Використовую відео оверлей: %s.\n"
#define MSGTR_LIBVO_VESA_CantInitializeVidixDriver "[VO_VESA] Не можу ініціялізувати драйвер VIDIX.\n"
#define MSGTR_LIBVO_VESA_UsingVidix "[VO_VESA] Використовую VIDIX.\n"
#define MSGTR_LIBVO_VESA_CantFindModeFor "[VO_VESA] Не можу знайти режим для: %ux%u@%u.\n"
#define MSGTR_LIBVO_VESA_InitializationComplete "[VO_VESA] Ініціялізація VESA завершена.\n"

// libvo/vesa_lvo.c
#define MSGTR_LIBVO_VESA_ThisBranchIsNoLongerSupported "[VESA_LVO] Ця гілка більше не підтримується.\n[VESA_LVO] Используйте -vo vesa:vidix взамен.\n"
#define MSGTR_LIBVO_VESA_CouldntOpen "[VESA_LVO] Не можу відкрити: '%s'\n"
#define MSGTR_LIBVO_VESA_InvalidOutputFormat "[VESA_LVI] Непридатний вихідний формат: %s(%0X)\n"
#define MSGTR_LIBVO_VESA_IncompatibleDriverVersion "[VESA_LVO] Версія вашого драйвера fb_vid несумісна з цією версією MPlayer!\n"

// libvo/vo_x11.c
#define MSGTR_LIBVO_X11_DrawFrameCalled "[VO_X11] Викликано draw_frame()!!!!!!\n"

// libvo/vo_xv.c
#define MSGTR_LIBVO_XV_DrawFrameCalled "[VO_XV] Викликано draw_frame()!!!!!!\n"
#define MSGTR_LIBVO_XV_SharedMemoryNotSupported "[VO_XV] Разділяєма пам'ять не підтримується\nПовернення до звичайного Xv.\n"
#define MSGTR_LIBVO_XV_XvNotSupportedByX11 "[VO_XV] На жаль, Xv не підтримується цією версією/драйвером X11\n[VO_XV] ******** Попробуйте -vo x11  или  -vo sdl  *********\n"
#define MSGTR_LIBVO_XV_XvQueryAdaptorsFailed  "[VO_XV] Помилка XvQueryAdaptors.\n"
#define MSGTR_LIBVO_XV_InvalidPortParameter "[VO_XV] Непридатний параметр port, перевизначення параметром port 0.\n"
#define MSGTR_LIBVO_XV_CouldNotGrabPort "[VO_XV] Немождиво захопити порт %i.\n"
#define MSGTR_LIBVO_XV_CouldNotFindFreePort "[VO_XV] Неможливо знайти вільній Xvideo-порт - можливо інший додаток вже\n"\
"[VO_XV] його використовує. Закрийте всі відео-додатки і спробуйте знову. Якщо це\n"\
"[VO_XV] не допомогає, дивіться 'mplayer -vo help' для інших (не-xv) драйверів відео-виводу.\n"
#define MSGTR_LIBVO_XV_NoXvideoSupport "[VO_XV] Схоже, що ваша відео-карта не має підтримки Xvideo.\n"\
"[VO_XV] Запустіть 'xvinfo', щоб перевірити підтримку Xv і читайте \n"\
"[VO_XV] DOCS/HTML/uk/video.html#xv!\n"\
"[VO_XV] Дивіться 'mplayer -vo help' для інших (не-xv) драйверів відео-виводу.\n"\
"[VO_XV] Спробуйте -vo x11.\n"
#define MSGTR_VO_XV_ImagedimTooHigh "Розміри зображення джерела надто великі: %ux%u (максимум %ux%u)\n"

// vo_yuv4mpeg.c
#define MSGTR_VO_YUV4MPEG_InterlacedHeightDivisibleBy4 "Для режима з чергуванням рядків необхідно, щоб висота зображеня ділилася на 4."
#define MSGTR_VO_YUV4MPEG_InterlacedLineBufAllocFail "Неможливо виділити пам'ять для лінійного буфера в режимі з чергуванням рядків."
#define MSGTR_VO_YUV4MPEG_WidthDivisibleBy2 "Ширина зображення повинна ділитися на 2."
#define MSGTR_VO_YUV4MPEG_OutFileOpenError "Не можу виділити пам'ять або файловий дескриптор для запису \"%s\"!"
#define MSGTR_VO_YUV4MPEG_OutFileWriteError "Помилка запису зображення в вивід!"
#define MSGTR_VO_YUV4MPEG_UnknownSubDev "Невідомий субпристрій: %s"
#define MSGTR_VO_YUV4MPEG_InterlacedTFFMode "Використовую режим виводу з чергуванням рядків, верхнє поле - перше."
#define MSGTR_VO_YUV4MPEG_InterlacedBFFMode "Використовую режим виводу з чергуванням рядків, нижнє поле - перше."
#define MSGTR_VO_YUV4MPEG_ProgressiveMode "Використовую (типово) прогресивний режим кадрів."

// vosub_vidix.c
#define MSGTR_LIBVO_SUB_VIDIX_CantStartPlayback "[VO_SUB_VIDIX] Не можу почати відтворення: %s\n"
#define MSGTR_LIBVO_SUB_VIDIX_CantStopPlayback "[VO_SUB_VIDIX] Не можу зупинити відтворення: %s\n"
#define MSGTR_LIBVO_SUB_VIDIX_InterleavedUvForYuv410pNotSupported "[VO_SUB_VIDIX] UV з чергуванням рядкыв для YUV410P не пыдтримуэться.\n"
#define MSGTR_LIBVO_SUB_VIDIX_DummyVidixdrawsliceWasCalled "[VO_SUB_VIDIX] Був викликаний фіктивний vidix_draw_slice().\n"
#define MSGTR_LIBVO_SUB_VIDIX_DummyVidixdrawframeWasCalled "[VO_SUB_VIDIX] Був викликаний фіктивний vidix_draw_frame().\n"
#define MSGTR_LIBVO_SUB_VIDIX_UnsupportedFourccForThisVidixDriver "[VO_SUB_VIDIX] Непідтримуваний FourCC для цього драйвера VIDIX: %x (%s).\n"
#define MSGTR_LIBVO_SUB_VIDIX_VideoServerHasUnsupportedResolution "[VO_SUB_VIDIX] Відео-сервер не підтримує дозвіл (%dx%d), підтримується: %dx%d-%dx%d.\n"
#define MSGTR_LIBVO_SUB_VIDIX_VideoServerHasUnsupportedColorDepth "[VO_SUB_VIDIX] Відео-сервер не підтримує глибину колору vidix (%d).\n"
#define MSGTR_LIBVO_SUB_VIDIX_DriverCantUpscaleImage "[VO_SUB_VIDIX] Драйвер VIDIX не може збільшити масштаб зображення (%d%d -> %d%d).\n"
#define MSGTR_LIBVO_SUB_VIDIX_DriverCantDownscaleImage "[VO_SUB_VIDIX] Драйвер VIDIX не може зменшити масштаб зображення (%d%d -> %d%d).\n"
#define MSGTR_LIBVO_SUB_VIDIX_CantConfigurePlayback "[VO_SUB_VIDIX] Не можу налаштувати відтворення: %s.\n"
#define MSGTR_LIBVO_SUB_VIDIX_YouHaveWrongVersionOfVidixLibrary "[VO_SUB_VIDIX] Маєте невірну версію бібліотеки VIDIX.\n"
#define MSGTR_LIBVO_SUB_VIDIX_CouldntFindWorkingVidixDriver "[VO_SUB_VIDIX] Неможливо знайти рабочий драйвер VIDIX.\n"
#define MSGTR_LIBVO_SUB_VIDIX_CouldntGetCapability "[VO_SUB_VIDIX] Неможливо отримати здатність: %s.\n"

// x11_common.c
#define MSGTR_EwmhFullscreenStateFailed "\nX11: Неможливо відіслати подію EWMH fullscreen!\n"
#define MSGTR_CouldNotFindXScreenSaver "xscreensaver_disable: Неможливо знайти вікно XScreenSaver'а.\n"
#define MSGTR_SelectedVideoMode "XF86VM: Вибрано відеорежим %dx%d для розміру зображення %dx%d.\n"

#define MSGTR_InsertingAfVolume "[Мікшер] Немає апаратного мікшування, вставляю фільтр гучності.\n"
#define MSGTR_NoVolume "[Мікшер] Немає доступного керування гучності.\n"
#define MSGTR_NoBalance "[Мікшер] Немає доступного керування балансом.\n"

// old vo drivers that have been replaced
#define MSGTR_VO_PGM_HasBeenReplaced "Драйвер відеовиводу pgm було змінено на -vo pnm:pgmyuv.\n"
#define MSGTR_VO_MD5_HasBeenReplaced "Драйвер відеовиводу md5 було змінено на -vo md5sum.\n"


// ======================= audio output drivers ========================

// audio_out.c
#define MSGTR_AO_ALSA9_1x_Removed "audio_out: модулі alsa9 та alsa1x були видалені, використовуйте -ao alsa.\n"
#define MSGTR_AO_NoSuchDriver "відсутній аудіо-драйвер '%.*s'\n"
#define MSGTR_AO_FailedInit "Збій ініціалізації аудіо-драйвера '%s'\n"

// ao_oss.c
#define MSGTR_AO_OSS_CantOpenMixer "[AO OSS] audio_setup: Не можу відкрити пристрій мікшера %s: %s\n"
#define MSGTR_AO_OSS_ChanNotFound "[AO OSS] audio_setup: Мікшер аудіо-карти не має  каналу '%s', використовується типовий канал.\n"
#define MSGTR_AO_OSS_CantOpenDev "[AO OSS] audio_setup: Не можу відкрити аудіо-пристрій %s: %s\n"
#define MSGTR_AO_OSS_CantMakeFd "[AO OSS] audio_setup: Не можу заблокувати файловий дескриптор: %s\n"
#define MSGTR_AO_OSS_CantSet "[AO OSS] Не можу встановити аудіо-пристрій %s до %s виводу, пробую %s...\n"
#define MSGTR_AO_OSS_CantSetChans "[AO OSS] audio_setup: Збій при встановлені аудіо-пристрою в %d-канальный режим.\n"
#define MSGTR_AO_OSS_CantUseGetospace "[AO OSS] audio_setup: драйвер не підтримує SNDCTL_DSP_GETOSPACE :-(\n"
#define MSGTR_AO_OSS_CantUseSelect "[AO OSS]\n   ***  Ваш аудіо-драйвер НЕ підтримує select()  ***\n Перекомпілюйте MPlayer з #undef HAVE_AUDIO_SELECT в config.h !\n\n"
#define MSGTR_AO_OSS_CantReopen "[AO OSS] Фатальна помилка:\n*** НЕ МОЖУ ПУКУВІДКРИТИ / СКИНУТИ АУДІО-ПРИСТРІЙ *** %s\n"
#define MSGTR_AO_OSS_UnknownUnsupportedFormat "[AO OSS] Невідомий/Непідтримуваний формат OSS: %x.\n"

// ao_arts.c
#define MSGTR_AO_ARTS_CantInit "[AO ARTS] %s\n"
#define MSGTR_AO_ARTS_ServerConnect "[AO ARTS] Під'єднано до звукового сервера.\n"
#define MSGTR_AO_ARTS_CantOpenStream "[AO ARTS] Неможливо відкрити потік.\n"
#define MSGTR_AO_ARTS_StreamOpen "[AO ARTS] Потік відкрито.\n"
#define MSGTR_AO_ARTS_BufferSize "[AO ARTS] розмір буфера: %d\n"

// ao_dxr2.c
#define MSGTR_AO_DXR2_SetVolFailed "[AO DXR2] Не вдалося встановити гучніть в %d.\n"
#define MSGTR_AO_DXR2_UnsupSamplerate "[AO DXR2] dxr2: %d Гц не підтримується, спробуйте змінити частоту дискретизації.\n"

// ao_esd.c
#define MSGTR_AO_ESD_CantOpenSound "[AO ESD] Збій esd_open_sound: %s\n"
#define MSGTR_AO_ESD_LatencyInfo "[AO ESD] затримка: [сервер: %0.2fs, мережа: %0.2fs] (підлаштування %0.2fs)\n"
#define MSGTR_AO_ESD_CantOpenPBStream "[AO ESD] не вдалося віткрити потік програвання ESD: %s\n"

// ao_mpegpes.c
#define MSGTR_AO_MPEGPES_CantSetMixer "[AO MPEGPES] Не вдалося встановити мікшер DVB-аудио: %s\n"
#define MSGTR_AO_MPEGPES_UnsupSamplerate "[AO MPEGPES] %d Гц не підтримується, спробуйте змінити частоту дискретизації.\n"

// ao_pcm.c
#define MSGTR_AO_PCM_FileInfo "[AO PCM] Файл: %s (%s)\nPCM: Частота дискретизації: %i Гц Канали: %s Формат %s\n"
#define MSGTR_AO_PCM_HintInfo "[AO PCM] Інформація: найшвидший дамп досягається з -benchmark -vc null -vo null -ao pcm:fast\n[AO PCM]: Інформація: Для запису WAVE-файлів використовуйте -ao pcm:waveheader (типово).\n"
#define MSGTR_AO_PCM_CantOpenOutputFile "[AO PCM] Збій відкриття %s для запису!\n"

// ao_sdl.c
#define MSGTR_AO_SDL_INFO "[AO SDL] Частота дискретизації: %i Гц Канали: %s Формат %s\n"
#define MSGTR_AO_SDL_DriverInfo "[AO SDL] використовується аудіо-драйвер %s.\n"
#define MSGTR_AO_SDL_UnsupportedAudioFmt "[AO SDL] Непідтримуваний аудіо-формат: 0x%x.\n"
#define MSGTR_AO_SDL_CantInit "[AO SDL] Збій ініціалізіції SDL Audio: %s\n"
#define MSGTR_AO_SDL_CantOpenAudio "[AO SDL] Неможливо відкрити аудіо: %s\n"

// ao_sgi.c
#define MSGTR_AO_SGI_INFO "[AO SGI] керування.\n"
#define MSGTR_AO_SGI_InitInfo "[AO SGI] init: Частота дискретизації: %i Гц Канали: %s Формат %s\n"
#define MSGTR_AO_SGI_InvalidDevice "[AO SGI] play: непридатний пристрій.\n"
#define MSGTR_AO_SGI_CantSetParms_Samplerate "[AO SGI] init: збій setparams: %s\nНеможливо встановити бажану частоту дискретизації.\n"
#define MSGTR_AO_SGI_CantSetAlRate "[AO SGI] init: AL_RATE не доступний на заданому ресурсі.\n"
#define MSGTR_AO_SGI_CantGetParms "[AO SGI] init: збій getparams: %s\n"
#define MSGTR_AO_SGI_SampleRateInfo "[AO SGI] init: частота дискретизації зараз %f (бажана частота %f)\n"
#define MSGTR_AO_SGI_InitConfigError "[AO SGI] init: %s\n"
#define MSGTR_AO_SGI_InitOpenAudioFailed "[AO SGI] init: Неможливо відкрити аудио-канал: %s\n"
#define MSGTR_AO_SGI_Uninit "[AO SGI] uninit: ...\n"
#define MSGTR_AO_SGI_Reset "[AO SGI] reset: ...\n"
#define MSGTR_AO_SGI_PauseInfo "[AO SGI] audio_pause: ...\n"
#define MSGTR_AO_SGI_ResumeInfo "[AO SGI] audio_resume: ...\n"

// ao_sun.c
#define MSGTR_AO_SUN_RtscSetinfoFailed "[AO SUN] rtsc: Збій SETINFO.\n"
#define MSGTR_AO_SUN_RtscWriteFailed "[AO SUN] rtsc: збій запису."
#define MSGTR_AO_SUN_CantOpenAudioDev "[AO SUN] Не можу відкрити аудіо-пристрій %s, %s -> nosound.\n"
#define MSGTR_AO_SUN_UnsupSampleRate "[AO SUN] audio_setup: ваша карта не підтримує канал %d, %s, частоту дискретизации %d Гц.\n"
#define MSGTR_AO_SUN_CantUseSelect "[AO SUN]\n   ***  Ваш аудіо-драйвер НЕ підтримує select()  ***\nПерекомпілюйте MPlayer з #undef HAVE_AUDIO_SELECT в config.h !\n\n"
#define MSGTR_AO_SUN_CantReopenReset "[AO SUN] Фатальная ошибка:\n*** НЕ МОЖУ ПЕРЕВІДКРИТИ / СКИНУТИ АУДІО-ПРИСТРІЙ (%s) ***\n"

// ao_alsa.c
#define MSGTR_AO_ALSA_InvalidMixerIndexDefaultingToZero "[AO_ALSA] Непридатний індекс мікшера. Повертаю до 0.\n"
#define MSGTR_AO_ALSA_MixerOpenError "[AO_ALSA] Помилка відкриття мікшера: %s\n"
#define MSGTR_AO_ALSA_MixerAttachError "[AO_ALSA] Помилка приєднання %s до мікшера: %s\n"
#define MSGTR_AO_ALSA_MixerRegisterError "[AO_ALSA] Помилка реєстрації мікшера: %s\n"
#define MSGTR_AO_ALSA_MixerLoadError "[AO_ALSA] Помилка завантаження мікшера: %s\n"
#define MSGTR_AO_ALSA_UnableToFindSimpleControl "[AO_ALSA] Неможливо знайти простий елемент керування '%s',%i.\n"
#define MSGTR_AO_ALSA_ErrorSettingLeftChannel "[AO_ALSA] Помилка установки лівого каналу, %s\n"
#define MSGTR_AO_ALSA_ErrorSettingRightChannel "[AO_ALSA] Полмилка установки правого каналу, %s\n"
#define MSGTR_AO_ALSA_CommandlineHelp "\n[AO_ALSA] підказка командного рядка -ao alsa:\n"\
"[AO_ALSA] Приклад: mplayer -ao alsa:device=hw=0.3\n"\
"[AO_ALSA]   Встанавлює четвертий пристрій першої карти.\n\n"\
"[AO_ALSA] Опції:\n"\
"[AO_ALSA]   noblock\n"\
"[AO_ALSA]     Відкриває пристрій в неблокуючому режимі.\n"\
"[AO_ALSA]   device=<им'я-пристрою>\n"\
"[AO_ALSA]     Встанавлює пристрій (замініть , на . і : на =)\n"
#define MSGTR_AO_ALSA_ChannelsNotSupported "[AO_ALSA] %d каналів не подтримується.\n"
#define MSGTR_AO_ALSA_OpenInNonblockModeFailed "[AO_ALSA] Збій відткриття в неблокуючому режимі, спроба відкрити в блокуючому режимі.\n"
#define MSGTR_AO_ALSA_PlaybackOpenError "[AO_ALSA] Помилка відкриття відтворення: %s\n"
#define MSGTR_AO_ALSA_ErrorSetBlockMode "[AL_ALSA] Помилка установки блокуючого режиму: %s.\n"
#define MSGTR_AO_ALSA_UnableToGetInitialParameters "[AO_ALSA] Неможливо отримати початкові параметры: %s\n"
#define MSGTR_AO_ALSA_UnableToSetAccessType "[AO_ALSA] Неможливо встановити тип доступу: %s\n"
#define MSGTR_AO_ALSA_FormatNotSupportedByHardware "[AO_ALSA] Формат %s не підтримується обладнанням, пробуєм типові значення.\n"
#define MSGTR_AO_ALSA_UnableToSetFormat "[AO_ALSA] Неможливо втановити формат: %s\n"
#define MSGTR_AO_ALSA_UnableToSetChannels "[AO_ALSA] Неможливо встановити канали: %s\n"
#define MSGTR_AO_ALSA_UnableToDisableResampling "[AO_ALSA] Неможливо відключити ресемплінг: %s\n"
#define MSGTR_AO_ALSA_UnableToSetSamplerate2 "[AO_ALSA] Неможливо встановити частоту дискретизації-2: %s\n"
#define MSGTR_AO_ALSA_UnableToSetBufferTimeNear "[AO_ALSA] Неможливо встановити приблизний час буфера: %s\n"
#define MSGTR_AO_ALSA_UnableToGetPeriodSize "[AO ALSA] Неможливо отримати розмір періода: %s\n"
#define MSGTR_AO_ALSA_UnableToSetPeriods "[AO_ALSA] Неможливо встановити періоди: %s\n"
#define MSGTR_AO_ALSA_UnableToSetHwParameters "[AO_ALSA] Неможливо встановити hw-параметри: %s\n"
#define MSGTR_AO_ALSA_UnableToGetBufferSize "[AO_ALSA] Неможливо отримати buffersize: %s\n"
#define MSGTR_AO_ALSA_UnableToGetSwParameters "[AO_ALSA] Неможливо отримати sw-параметри: %s\n"
#define MSGTR_AO_ALSA_UnableToSetSwParameters "[AO_ALSA] Неможливо встановити sw-параметри: %s\n"
#define MSGTR_AO_ALSA_UnableToGetBoundary "[AO_ALSA] Неможливо отримати межу: %s\n"
#define MSGTR_AO_ALSA_UnableToSetStartThreshold "[AO_ALSA] Неможливо встановити поріг запуску: %s\n"
#define MSGTR_AO_ALSA_UnableToSetStopThreshold "[AO_ALSA] Неможливо встановити поріг зупинки: %s\n"
#define MSGTR_AO_ALSA_UnableToSetSilenceSize "[AO_ALSA] Неможливо встановити розмір тиші: %s\n"
#define MSGTR_AO_ALSA_PcmCloseError "[AO_ALSA] помилка закриття pcm: %s\n"
#define MSGTR_AO_ALSA_NoHandlerDefined "[AO_ALSA] Не визначений обробник!\n"
#define MSGTR_AO_ALSA_PcmPrepareError "[AO_ALSA] помилка підготовки pcm: %s\n"
#define MSGTR_AO_ALSA_PcmPauseError "[AO_ALSA] помилка паузи pcm: %s\n"
#define MSGTR_AO_ALSA_PcmDropError "[AO_ALSA] помилка скидання pcm: %s\n"
#define MSGTR_AO_ALSA_PcmResumeError "[AO_ALSA] помилка відновлення pcm: %s\n"
#define MSGTR_AO_ALSA_DeviceConfigurationError "[AO_ALSA] Помилка настройки пристрою."
#define MSGTR_AO_ALSA_PcmInSuspendModeTryingResume "[AO_ALSA] Pcm в режимі очікування, спроба відновлення.\n"
#define MSGTR_AO_ALSA_WriteError "[AO_ALSA] Помилка запису: %s\n"
#define MSGTR_AO_ALSA_TryingToResetSoundcard "[AO_ALSA] Спроба скинути звукову карту.\n"
#define MSGTR_AO_ALSA_CannotGetPcmStatus "[AO_ALSA] Неможливо отримати стан pcm: %s\n"

// ao_plugin.c
#define MSGTR_AO_PLUGIN_InvalidPlugin "[AO ПЛАГИН] непридатний плагін: %s\n"


// ======================= audio filters ================================

// af_scaletempo.c
#define MSGTR_AF_ValueOutOfRange MSGTR_VO_ValueOutOfRange

// af_ladspa.c
#define MSGTR_AF_LADSPA_AvailableLabels "доступні мітки в"
#define MSGTR_AF_LADSPA_WarnNoInputs "ПОПЕРЕДЖЕННЯ! Цей LADSPA-плагін не має аудіо-входів.\n  Вхідний аудіо-сигнал буде втрачено."
#define MSGTR_AF_LADSPA_ErrMultiChannel "Мультиканальні (>2) плагіны наразі не підтримуються.\n  Використовуйте тільки моно- та стерео-плагіни."
#define MSGTR_AF_LADSPA_ErrNoOutputs "Цей LADSPA-плагін не має аудіо-виходів."
#define MSGTR_AF_LADSPA_ErrInOutDiff "Число аудиовходов и аудиовыходов у LADSPA плагина отличается."
#define MSGTR_AF_LADSPA_ErrFailedToLoad "сбой загрузки"
#define MSGTR_AF_LADSPA_ErrNoDescriptor "Неможливо знайти функцію ladspa_descriptor() у вказаному файлі бібліотеки."
#define MSGTR_AF_LADSPA_ErrLabelNotFound "Неможливо знайти мітку в бібліотеці плагіна."
#define MSGTR_AF_LADSPA_ErrNoSuboptions "Не вказаны субопції."
#define MSGTR_AF_LADSPA_ErrNoLibFile "Не вказаний файл бібліотеки."
#define MSGTR_AF_LADSPA_ErrNoLabel "Не вказана мітка фільтра."
#define MSGTR_AF_LADSPA_ErrNotEnoughControls "Недостатньо налаштувань вказано в командному рядку."
#define MSGTR_AF_LADSPA_ErrControlBelow "%s: Вхідний параметр #%d менше нижньої межі %0.4f.\n"
#define MSGTR_AF_LADSPA_ErrControlAbove "%s: Вхідний параметр #%d більше верхньої межі %0.4f.\n"


// ========================== INPUT =========================================

// joystick.c
#define MSGTR_INPUT_JOYSTICK_CantOpen "Не можу відкрити пристрій джойстика %s: %s\n"
#define MSGTR_INPUT_JOYSTICK_ErrReading "Помилка під час читання пристрою джойстика: %s\n"
#define MSGTR_INPUT_JOYSTICK_LoosingBytes "Joystick: Ми втратили %d байт(и/ів) даних\n"
#define MSGTR_INPUT_JOYSTICK_WarnLostSync "Joystick: попередження про init-випадок, ми втратили синхронізацію з драйвером.\n"
#define MSGTR_INPUT_JOYSTICK_WarnUnknownEvent "Joystick: попередження про невідомий тип випадку %d\n"

// appleir.c
#define MSGTR_INPUT_APPLE_IR_CantOpen "Не можу вікрити пристрій Apple IR: %s\n"

// input.c
#define MSGTR_INPUT_INPUT_ErrCantRegister2ManyCmdFds "Надто багато дескрипторів командних файлів, неможливо зареєструвати файловий дескриптор %d.\n"
#define MSGTR_INPUT_INPUT_ErrCantRegister2ManyKeyFds "Надто багато дескрипторів файлів клавіш, неможливо зареєструвати файловий дескриптор %d.\n"
#define MSGTR_INPUT_INPUT_ErrArgMustBeInt "Команда %s: аргумент %d не є цілим числом.\n"
#define MSGTR_INPUT_INPUT_ErrArgMustBeFloat "Команда %s: аргумент %d не є дійсним числом.\n"
#define MSGTR_INPUT_INPUT_ErrUnterminatedArg "Команда %s: аргумент %d незавершений.\n"
#define MSGTR_INPUT_INPUT_ErrUnknownArg "Невідомий аргумент %d\n"
#define MSGTR_INPUT_INPUT_Err2FewArgs "Команда %s потребує не менш як %d аргументів, досі ми знашли лише %d.\n"
#define MSGTR_INPUT_INPUT_ErrReadingCmdFd "Помилка під час читання дескриптора командного файлу %d: %s\n"
#define MSGTR_INPUT_INPUT_ErrCmdBufferFullDroppingContent "Командний буфер файлового дескриптора %d заповнений: пропускаю вміст.\n"
#define MSGTR_INPUT_INPUT_ErrInvalidCommandForKey "Непридатна команда для прив'язки до клавіші %s"
#define MSGTR_INPUT_INPUT_ErrSelect "Помилка вибору: %s\n"
#define MSGTR_INPUT_INPUT_ErrOnKeyInFd "Помилка у файловому дескрипторі клавіш вводу %d\n"
#define MSGTR_INPUT_INPUT_ErrDeadKeyOnFd "Мертва клавіша вводу в файловому дескрипторі %d\n"
#define MSGTR_INPUT_INPUT_Err2ManyKeyDowns "Надто багато подій одночасного натиснення клавіш\n"
#define MSGTR_INPUT_INPUT_ErrOnCmdFd "Помилка в дескрипторі командного файлу %d\n"
#define MSGTR_INPUT_INPUT_ErrReadingInputConfig "Помилка під час читання конфігураційного файла вводу %s: %s\n"
#define MSGTR_INPUT_INPUT_ErrUnknownKey "Невідома клавіша '%s'\n"
#define MSGTR_INPUT_INPUT_ErrUnfinishedBinding "Незакінчена прив'язка %s\n"
#define MSGTR_INPUT_INPUT_ErrBuffer2SmallForKeyName "Буфер замалий для назви цієї клавіші: %s\n"
#define MSGTR_INPUT_INPUT_ErrNoCmdForKey "Не знайдено команди для клавіші %s"
#define MSGTR_INPUT_INPUT_ErrBuffer2SmallForCmd "Буфер замалий для команди %s\n"
#define MSGTR_INPUT_INPUT_ErrWhyHere "Що ми тут робимо?\n"
#define MSGTR_INPUT_INPUT_ErrCantInitJoystick "Неможливо иниціювати джойстик ввода\n"
#define MSGTR_INPUT_INPUT_ErrCantOpenFile "Неможливо відкрити %s: %s\n"
#define MSGTR_INPUT_INPUT_ErrCantInitAppleRemote "Неможливо иніціювати Apple Remote.\n"

// lirc.c
#define MSGTR_LIRCopenfailed "Збій відкриття підтримки LIRC. Ви не зможете скористатися вашим дистанційним керуванням.\n"
#define MSGTR_LIRCcfgerr "Збій читання файла конфігурації LIRC '%s'!\n"

// format.c
#define MSGTR_AF_FORMAT_UnknownFormat "неизвестный формат "


// open.c, stream.c:
#define MSGTR_CdDevNotfound "Компактовід \"%s\" не знайдений!\n"
#define MSGTR_ErrTrackSelect "Помилка вибору треку на VCD!"
#define MSGTR_ReadSTDIN "Читання з stdin...\n"
#define MSGTR_FileNotFound "Файл не знайдений: '%s'\n"

#define MSGTR_SMBFileNotFound "Помилка відкриття з мережі: '%s'\n"

#define MSGTR_CantOpenDVD "Не зміг відкрити DVD: %s (%s)\n"
#define MSGTR_DVDnumTitles "Є %d доріжок з титрами на цьому DVD.\n"
#define MSGTR_DVDinvalidTitle "Неприпустимий номер доріжки титрів на DVD: %d\n"
#define MSGTR_DVDnumAngles "Є %d кутів на цій доріжці з DVD титрами.\n"
#define MSGTR_DVDinvalidAngle "Неприпустимий номер DVD кута: %d\n"
#define MSGTR_DVDnoIFO "Не можу відкрити IFO файл для DVD титрів %d.\n"
#define MSGTR_DVDnoVOBs "Не можу відкрити титри VOBS (VTS_%02d_1.VOB).\n"

// demuxer.c, demux_*.c:
#define MSGTR_AudioStreamRedefined "Попередження! Заголовок аудіо потоку %d перевизначений!\n"
#define MSGTR_VideoStreamRedefined "Попередження! Заголовок відео потоку %d перевизначений!\n"
#define MSGTR_TooManyAudioInBuffer "\nDEMUXER: Надто багато (%d, %d байтів) аудіо пакетів у буфері!\n"
#define MSGTR_TooManyVideoInBuffer "\nDEMUXER: Надто багато (%d, %d байтів) відео пакетів у буфері!\n"
#define MSGTR_MaybeNI "(можливо ви програєте неперемежений потік/файл або невдалий кодек)\n"
#define MSGTR_SwitchToNi "\nДетектовано погано перемежений AVI файл - переходжу в -ni режим...\n"
#define MSGTR_Detected_XXX_FileFormat "Знайдений %s формат файлу!\n"
#define MSGTR_FormatNotRecognized "========= Вибачте, формат цього файлу не розпізнаний чи не підтримується ===========\n"\
                                  "===== Якщо це AVI, ASF або MPEG потік, будь ласка зв'яжіться з автором! ======\n"
#define MSGTR_MissingVideoStream "Відео потік не знайдений!\n"
#define MSGTR_MissingAudioStream "Аудіо потік не знайдений...  -> програю без звуку\n"
#define MSGTR_MissingVideoStreamBug "Відео потік загублений!? Зв'яжіться з автором, це мабуть помилка :(\n"

#define MSGTR_DoesntContainSelectedStream "demux: файл не містить обраний аудіо або відео потік\n"

#define MSGTR_NI_Forced "Примусово вибраний"
#define MSGTR_NI_Detected "Знайдений"
#define MSGTR_NI_Message "%s НЕПЕРЕМЕЖЕНИЙ формат AVI файлу!\n"

#define MSGTR_UsingNINI "Використання НЕПЕРЕМЕЖЕНОГО або пошкодженого формату AVI файлу!\n"
#define MSGTR_CouldntDetFNo "Не зміг визначити число кадрів (для абсолютного перенесення)\n"
#define MSGTR_CantSeekRawAVI "Не можу переміститися у непроіндексованому потоці .AVI! (вимагається індекс, спробуйте з ключом -idx!)\n"
#define MSGTR_CantSeekFile "Не можу переміщуватися у цьому файлі!\n"

#define MSGTR_MOVcomprhdr "MOV: Стиснуті заголовки (поки що) не підтримуються!\n"
#define MSGTR_MOVvariableFourCC "MOV: Попередження! Знайдено перемінний FOURCC!?\n"
#define MSGTR_MOVtooManyTrk "MOV: Попередження! надто багато треків!"
#define MSGTR_ErrorOpeningOGGDemuxer "Неможливо відкрити ogg demuxer.\n"
#define MSGTR_CannotOpenAudioStream "Неможливо відкрити аудіо потік: %s\n"
#define MSGTR_CannotOpenSubtitlesStream "Неможливо відкрити потік субтитрів: %s\n"
#define MSGTR_OpeningAudioDemuxerFailed "Збій відкриття демультиплексора аудіо: %s\n"
#define MSGTR_OpeningSubtitlesDemuxerFailed "Збій відриття демультиплексора субтитрів: %s\n"
#define MSGTR_TVInputNotSeekable "По ТВ-входу неможливо переміщуватися! (Можливо, переміщення буде для зміни каналів ;)\n"
#define MSGTR_DemuxerInfoChanged "Інформація демультиплексора %s змінена на %s\n"
#define MSGTR_ClipInfo "Інформація про кліп:\n"

#define MSGTR_LeaveTelecineMode "\ndemux_mpg: виявлено NTSC-вміст з 30000/1001 кадр/сек, переключаю частоту кадрів.\n"
#define MSGTR_EnterTelecineMode "\ndemux_mpg: виявлено NTSC-вміст з 24000/1001 кадр/сек з порядковим розгортанням, переключаю частоту кадрів.\n"

#define MSGTR_CacheFill "\rЗаповнення кэшу: %5.2f%% (%"PRId64" байт(и,ів))   "
#define MSGTR_NoBindFound "Не знайдена прив'язка до клавіші '%s'.\n"
#define MSGTR_FailedToOpen "Збій відкриття %s.\n"

#define MSGTR_VideoID "[%s] Знайдено відеопотік, -vid %d\n"
#define MSGTR_AudioID "[%s] Знайдено аудіопотік, -aid %d\n"
#define MSGTR_SubtitleID "[%s] Знайдено потік субтитрів, -sid %d\n"

// asfheader.c
#define MSGTR_MPDEMUX_ASFHDR_HeaderSizeOver1MB "ФАТАЛЬНА ПОМИЛКА: розмір заголовка більший за 1 MB (%d)!\nБудь-ласка, зв'яжіться з авторами MPlayer'а і завантажте/відішліть цей файл.\n"
#define MSGTR_MPDEMUX_ASFHDR_HeaderMallocFailed "Не можу виділити %d байт(и,ів) для заголовка.\n"
#define MSGTR_MPDEMUX_ASFHDR_EOFWhileReadingHeader "EOF при читанні заголовка ASF, зламаний/неповний файл?\n"
#define MSGTR_MPDEMUX_ASFHDR_DVRWantsLibavformat "DVR, мабуть, буде працювати лише з libavformat, спробуйте -demuxer 35, якщо маєте проблеми\n"
#define MSGTR_MPDEMUX_ASFHDR_NoDataChunkAfterHeader "Нема ланки даных, слідуючих за заголовком!\n"
#define MSGTR_MPDEMUX_ASFHDR_AudioVideoHeaderNotFound "ASF: не знайдено аудіо- або відеозаголовка - зламаний файл?\n"
#define MSGTR_MPDEMUX_ASFHDR_InvalidLengthInASFHeader "Непридатна довжина в заголовці ASF!\n"
#define MSGTR_MPDEMUX_ASFHDR_DRMLicenseURL "URL ліцензії DRM: %s\n"
#define MSGTR_MPDEMUX_ASFHDR_DRMProtected "Файл обтяжений DRM-шифруванням, він не буде відтворюватися в MPlayer!\n"

// aviheader.c
#define MSGTR_MPDEMUX_AVIHDR_EmptyList "** порожній список?!\n"
#define MSGTR_MPDEMUX_AVIHDR_WarnNotExtendedAVIHdr "** Попередження: це не разширений заголовок AVI..\n"
#define MSGTR_MPDEMUX_AVIHDR_BuildingODMLidx "AVI: ODML: Побудова індекса ODML (%d ланок суперіндекса).\n"
#define MSGTR_MPDEMUX_AVIHDR_BrokenODMLfile "AVI: ODML: Виявлено зламаний (неповний?) файл. Буде використано традиційний індекс.\n"
#define MSGTR_MPDEMUX_AVIHDR_CantReadIdxFile "Неможливо прочитати файл індекса %s: %s\n"
#define MSGTR_MPDEMUX_AVIHDR_NotValidMPidxFile "%s не є придатним файлом індекса MPlayer.\n"
#define MSGTR_MPDEMUX_AVIHDR_FailedMallocForIdxFile "Не можу виділити пам'ять для даних індекса з %s.\n"
#define MSGTR_MPDEMUX_AVIHDR_PrematureEOF "передчасний кінець індексного файлу %s\n"
#define MSGTR_MPDEMUX_AVIHDR_IdxFileLoaded "Завантажено індексний файл: %s\n"
#define MSGTR_MPDEMUX_AVIHDR_GeneratingIdx "Генерується Індекс: %3lu %s     \r"
#define MSGTR_MPDEMUX_AVIHDR_IdxGeneratedForHowManyChunks "AVI: Згенеровано індексну таблицю для %d ланок!\n"
#define MSGTR_MPDEMUX_AVIHDR_Failed2WriteIdxFile "Не можу записати файл індекса %s: %s\n"
#define MSGTR_MPDEMUX_AVIHDR_IdxFileSaved "Збережено індексный файл: %s\n"

// demux_audio.c
#define MSGTR_MPDEMUX_AUDIO_BadID3v2TagSize "Аудіо-демультиплексор: поганий размір ID3v2-тага: більший, ніж потік (%u).\n"
#define MSGTR_MPDEMUX_AUDIO_DamagedAppendedID3v2Tag "Аудіо-демультиплексор: виявлено пошкоджений приєднаний ID3v2-таг.\n"
#define MSGTR_MPDEMUX_AUDIO_UnknownFormat "Аудіо-демультиплексор: невідомий формат %d.\n"

// demux_demuxers.c
#define MSGTR_MPDEMUX_DEMUXERS_FillBufferError "помилка fill_buffer: поганий демультиплексор: не vd, ad чи sd.\n"

// demux_mkv.c
#define MSGTR_MPDEMUX_MKV_ZlibInitializationFailed "[mkv] збій инициалізації zlib.\n"
#define MSGTR_MPDEMUX_MKV_ZlibDecompressionFailed "[mkv] збій zlib-розпакування.\n"
#define MSGTR_MPDEMUX_MKV_LzoInitializationFailed "[mkv] збій инициалізації lzo.\n"
#define MSGTR_MPDEMUX_MKV_LzoDecompressionFailed "[mkv] збій lzo-розпакування.\n"
#define MSGTR_MPDEMUX_MKV_TrackEncrypted "[mkv] Доріжка номер %u зашифрована і расшифровка ще не реалізована.\n[mkv] Пропуск доріжки.\n"
#define MSGTR_MPDEMUX_MKV_UnknownContentEncoding "[mkv] Невідомий тип шифрування вмісту для доріжки %u. Пропуск доріжки.\n"
#define MSGTR_MPDEMUX_MKV_UnknownCompression "[mkv] Доріжка %u стиснута невідомим/непідтримуваним алгоритмом (%u).\n[mkv] Пропуск доріжки.\n"
#define MSGTR_MPDEMUX_MKV_ZlibCompressionUnsupported "[mkv] Доріжка %u стиснута zlib, але mplayer скомпільовано без підтримки стиснення zlib.\n[mkv] Пропуск доріжки.\n"
#define MSGTR_MPDEMUX_MKV_TrackIDName "[mkv] ID доріжки %u: %s (%s) \"%s\", %s\n"
#define MSGTR_MPDEMUX_MKV_TrackID "[mkv] ID доріжки %u: %s (%s), %s\n"
#define MSGTR_MPDEMUX_MKV_UnknownCodecID "[mkv] Невідомий/непідтримуваний CodecID (%s) фбо відсутні/погані дані CodecPrivate (доріжка %u).\n"
#define MSGTR_MPDEMUX_MKV_FlacTrackDoesNotContainValidHeaders "[mkv] Доріжка FLAC не містить придатних заголовків.\n"
#define MSGTR_MPDEMUX_MKV_UnknownAudioCodec "[mkv] Невідомий/непідтримуваний ID аудіо-кодека '%s' для доріжки %u або відсутні/зіпсовані приватні дані кодека.\n"
#define MSGTR_MPDEMUX_MKV_SubtitleTypeNotSupported "[mkv] Тип субтитрів '%s' не подтримується.\n"
#define MSGTR_MPDEMUX_MKV_WillPlayVideoTrack "[mkv] Буде відтворюватися доріжка %u.\n"
#define MSGTR_MPDEMUX_MKV_NoVideoTrackFound "[mkv] Не знайдена/потребується відео-доріжка.\n"
#define MSGTR_MPDEMUX_MKV_NoAudioTrackFound "[mkv] Не знайдена/потребується аудіо-доріжка.\n"
#define MSGTR_MPDEMUX_MKV_WillDisplaySubtitleTrack "[mkv] Буде відображуватися доріжка субтитрів %u.\n"
#define MSGTR_MPDEMUX_MKV_NoBlockDurationForSubtitleTrackFound "[mkv] Попередження: Не знайдено BlockDuration для доріжки субтитрів.\n"
#define MSGTR_MPDEMUX_MKV_TooManySublines "[mkv] Попередження: слишком много строк для рендеринга, пропущены.\n"
#define MSGTR_MPDEMUX_MKV_TooManySublinesSkippingAfterFirst "\n[mkv] Попередження: надто багато субрядків для рендерингу, пропускаю всі крім першої %i.\n"

// demux_nuv.c
#define MSGTR_MPDEMUX_NUV_NoVideoBlocksInFile "У файлі нема відео-блоків.\n"

// demux_xmms.c
#define MSGTR_MPDEMUX_XMMS_FoundPlugin "Знайдено плагін: %s (%s).\n"
#define MSGTR_MPDEMUX_XMMS_ClosingPlugin "Закриваю плагін: %s.\n"
#define MSGTR_MPDEMUX_XMMS_WaitForStart "Очікування початку відтворення '%s' плагіном XMMS...\n"


// ========================== LIBMPCODECS ===================================

// dec_video.c & dec_audio.c:
#define MSGTR_CantOpenCodec "Не зміг відкрити кодек\n"
#define MSGTR_CantCloseCodec "Не зміг закрити кодек\n"

#define MSGTR_MissingDLLcodec "ПОМИЛКА: Не зміг відкрити необхідний DirectShow кодек: %s\n"
#define MSGTR_ACMiniterror "Не зміг завантажити чи ініціалізувати Win32/ACM AUDIO кодек (загублений DLL файл?)\n"
#define MSGTR_MissingLAVCcodec "Не можу знайти кодек \"%s\" у libavcodec...\n"

#define MSGTR_MpegNoSequHdr "MPEG: FATAL: КІНЕЦЬ ФАЙЛУ при пошуку послідовності заголовків\n"
#define MSGTR_CannotReadMpegSequHdr "FATAL: Не можу читати послідовність заголовків!\n"
#define MSGTR_CannotReadMpegSequHdrEx "FATAL: Не мочу читати розширення послідовності заголовків!\n"
#define MSGTR_BadMpegSequHdr "MPEG: Погана послідовність заголовків!\n"
#define MSGTR_BadMpegSequHdrEx "MPEG: Погане розширення послідовності заголовків!\n"

#define MSGTR_ShMemAllocFail "Не можу захопити загальну пам'ять\n"
#define MSGTR_CantAllocAudioBuf "Не можу захопити вихідний буфер аудіо\n"

#define MSGTR_UnknownAudio "Невідомий чи загублений аудіо формат, програю без звуку\n"

#define MSGTR_UsingExternalPP "[PP] Використовую зовнішній фільтр обробки, макс q = %d.\n"
#define MSGTR_UsingCodecPP "[PP] Використовую обробку кодека, макс q = %d.\n"
#define MSGTR_VideoCodecFamilyNotAvailableStr "Запрошений драйвер відео кодеку [%s] (vfm=%s) недосяжний (ввімкніть його під час компіляції)\n"
#define MSGTR_AudioCodecFamilyNotAvailableStr "Запрошений драйвер аудіо кодеку [%s] (afm=%s) недосяжний (ввімкніть його під час компіляції)\n"
#define MSGTR_OpeningVideoDecoder "Відкриваю відео декодер: [%s] %s\n"
#define MSGTR_OpeningAudioDecoder "Відкриваю аудіо декодер: [%s] %s\n"
#define MSGTR_VDecoderInitFailed "Збій ініціалізації VDecoder :(\n"
#define MSGTR_ADecoderInitFailed "Збій ініціалізації ADecoder :(\n"
#define MSGTR_ADecoderPreinitFailed "Збій підготування ADecoder :(\n"

// LIRC:
#define MSGTR_LIRCopenfailed "Невдале відкриття підтримки lirc!\n"
#define MSGTR_LIRCcfgerr "Невдале читання файлу конфігурації LIRC %s!\n"

// vf.c
#define MSGTR_CouldNotFindVideoFilter "Неможливо знайти відео фільтр '%s'\n"
#define MSGTR_CouldNotOpenVideoFilter "Неможливо відкрити відео фільтр '%s'\n"
#define MSGTR_OpeningVideoFilter "Відкриваю відео фільтр: "
//-----------------------------
#define MSGTR_CannotFindColorspace "Не можу підібрати загальну схему кольорів, навіть додавши 'scale' :(\n"

// vd.c
#define MSGTR_CouldNotFindColorspace "Не можу підібрати підходящу схему кольорів - повтор з -vf scale...\n"
#define MSGTR_MovieAspectIsSet "Відношення сторін %.2f:1 - масштабую аби скоректувати.\n"
#define MSGTR_MovieAspectUndefined "Відношення сторін не вказано - масштабування не використовується.\n"

// open.c, stream.c:
#define MSGTR_CdDevNotfound "CD-ROM \"%s\" не знайдений!\n"
#define MSGTR_ErrTrackSelect "Помилка вибору треку на VCD!"
#define MSGTR_ReadSTDIN "Читання з stdin...\n"
#define MSGTR_UnableOpenURL "Не можу відкрити URL: %s\n"
#define MSGTR_ConnToServer "З'єднання з сервером: %s\n"
#define MSGTR_FileNotFound "Файл не знайдений: '%s'\n"

#define MSGTR_SMBFileNotFound "Помилка відкриття з мережі: '%s'\n"
#define MSGTR_SMBNotCompiled "MPlayer не має вкомпільованої підтримки SMB\n"

#define MSGTR_CantOpenDVD "Не зміг відкрити DVD: %s (%s)\n"
#define MSGTR_DVDnumTitles "Є %d доріжок з титрами на цьому DVD.\n"
#define MSGTR_DVDinvalidTitle "Непридатний номер доріжки титрів на DVD: %d\n"
#define MSGTR_DVDnumChapters "Є %d розділів на цій доріжці з DVD титрами.\n"
#define MSGTR_DVDinvalidChapter "Непридатний номер DVD розділу: %d\n"
#define MSGTR_DVDnumAngles "Є %d кутів на цій доріжці з DVD титрами.\n"
#define MSGTR_DVDinvalidAngle "Непридатний номер DVD кута: %d\n"
#define MSGTR_DVDnoIFO "Не можу відкрити IFO файл для DVD титрів %d.\n"
#define MSGTR_DVDnoVOBs "Не можу відкрити титри VOBS (VTS_%02d_1.VOB).\n"
