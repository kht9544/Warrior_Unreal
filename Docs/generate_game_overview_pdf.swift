import AppKit
import CoreGraphics
import Foundation

enum BlockKind {
    case title, subtitle, meta, heading1, heading2, body, bullet, small, code
}

struct Block {
    let kind: BlockKind
    let text: String
}

let outputPath = CommandLine.arguments.count > 1
    ? CommandLine.arguments[1]
    : "Docs/Warrior_Game_Overview.pdf"

let pageWidth: CGFloat = 595.2
let pageHeight: CGFloat = 841.8
let marginX: CGFloat = 54
let marginTop: CGFloat = 56
let marginBottom: CGFloat = 54
let contentWidth = pageWidth - marginX * 2

let ink = NSColor(calibratedRed: 0.13, green: 0.14, blue: 0.17, alpha: 1)
let muted = NSColor(calibratedRed: 0.37, green: 0.39, blue: 0.43, alpha: 1)
let accent = NSColor(calibratedRed: 0.47, green: 0.16, blue: 0.10, alpha: 1)
let secondary = NSColor(calibratedRed: 0.09, green: 0.31, blue: 0.32, alpha: 1)
let rule = NSColor(calibratedRed: 0.82, green: 0.82, blue: 0.80, alpha: 1)
let pale = NSColor(calibratedRed: 0.98, green: 0.95, blue: 0.91, alpha: 1)

func font(_ size: CGFloat, weight: NSFont.Weight = .regular, mono: Bool = false) -> NSFont {
    if mono {
        return NSFont.monospacedSystemFont(ofSize: size, weight: weight)
    }
    return NSFont.systemFont(ofSize: size, weight: weight)
}

func paragraphStyle(lineHeight: CGFloat, spacingAfter: CGFloat = 0, firstLineHeadIndent: CGFloat = 0, headIndent: CGFloat = 0) -> NSMutableParagraphStyle {
    let style = NSMutableParagraphStyle()
    style.minimumLineHeight = lineHeight
    style.maximumLineHeight = lineHeight
    style.paragraphSpacing = spacingAfter
    style.firstLineHeadIndent = firstLineHeadIndent
    style.headIndent = headIndent
    style.lineBreakMode = .byWordWrapping
    return style
}

func attributes(for kind: BlockKind) -> [NSAttributedString.Key: Any] {
    switch kind {
    case .title:
        return [.font: font(27, weight: .bold), .foregroundColor: ink, .paragraphStyle: paragraphStyle(lineHeight: 35, spacingAfter: 8)]
    case .subtitle:
        return [.font: font(12.5), .foregroundColor: muted, .paragraphStyle: paragraphStyle(lineHeight: 18, spacingAfter: 10)]
    case .meta:
        return [.font: font(9.5), .foregroundColor: muted, .paragraphStyle: paragraphStyle(lineHeight: 14, spacingAfter: 6)]
    case .heading1:
        return [.font: font(17, weight: .bold), .foregroundColor: accent, .paragraphStyle: paragraphStyle(lineHeight: 24, spacingAfter: 8)]
    case .heading2:
        return [.font: font(12.8, weight: .semibold), .foregroundColor: secondary, .paragraphStyle: paragraphStyle(lineHeight: 18, spacingAfter: 4)]
    case .body:
        return [.font: font(10.4), .foregroundColor: ink, .paragraphStyle: paragraphStyle(lineHeight: 16.8, spacingAfter: 5)]
    case .bullet:
        return [.font: font(10), .foregroundColor: ink, .paragraphStyle: paragraphStyle(lineHeight: 15.8, spacingAfter: 4, headIndent: 13)]
    case .small:
        return [.font: font(8.6), .foregroundColor: muted, .paragraphStyle: paragraphStyle(lineHeight: 12.5, spacingAfter: 3)]
    case .code:
        return [.font: font(8.2, mono: true), .foregroundColor: NSColor(calibratedRed: 0.20, green: 0.18, blue: 0.16, alpha: 1), .paragraphStyle: paragraphStyle(lineHeight: 12.5, spacingAfter: 4)]
    }
}

func measuredHeight(_ block: Block, width: CGFloat) -> CGFloat {
    let attributed = NSAttributedString(string: block.text, attributes: attributes(for: block.kind))
    let rect = attributed.boundingRect(
        with: CGSize(width: width, height: .greatestFiniteMagnitude),
        options: [.usesLineFragmentOrigin, .usesFontLeading]
    )
    let base = ceil(rect.height)
    switch block.kind {
    case .heading1: return base + 12
    case .heading2: return base + 5
    case .title: return base + 6
    case .code: return base + 10
    default: return base + 4
    }
}

let blocks: [Block] = [
    Block(kind: .title, text: "Warrior 게임 설명서"),
    Block(kind: .subtitle, text: "도끼를 든 전사가 웨이브로 몰려오는 적을 상대하는 3인칭 액션 서바이벌 게임"),
    Block(kind: .meta, text: "작성일: 2026-05-30  |  기준 프로젝트: Warrior_Unreal"),
    Block(kind: .body, text: "Warrior는 Unreal Engine 기반의 3인칭 근접 액션 게임이다. 플레이어는 도끼를 장착한 전사가 되어 이동, 회피, 방어, 약공격, 강공격을 조합해 적 웨이브를 처치한다. 전투는 체력과 분노 게이지, 공격 타이밍, 방어 판정, 히트 리액션, 보스 체력바와 웨이브 UI를 중심으로 진행된다."),

    Block(kind: .heading1, text: "1. 게임 개요"),
    Block(kind: .body, text: "게임의 핵심 장르는 3인칭 액션 RPG 스타일의 웨이브 서바이벌이다. 기본 맵은 ThirdPersonMap이며, BP_SurvialGameMode와 DT_EenmyWaveSpawner를 통해 웨이브 단위로 적이 등장한다."),
    Block(kind: .code, text: "근거: Content/ThirdPerson/Maps/ThirdPersonMap.umap, Content/GameMode/BP_SurvialGameMode.uasset, Content/GameMode/DT_EenmyWaveSpawner.uasset"),
    Block(kind: .bullet, text: "• 시점: 캐릭터 뒤를 따라가는 3인칭 카메라"),
    Block(kind: .bullet, text: "• 플레이 방식: 적을 처치하며 웨이브를 넘기는 전투 중심 진행"),
    Block(kind: .bullet, text: "• 핵심 무기: 도끼 기반 근접 전투"),
    Block(kind: .bullet, text: "• 주요 자원: 체력, 분노 게이지, 무기/스킬 상태"),

    Block(kind: .heading1, text: "2. 플레이어 캐릭터"),
    Block(kind: .body, text: "플레이어 캐릭터는 HeroCharacter 계열 에셋과 C++ AWarriorHeroCharacter로 구성된다. 캐릭터는 SpringArm + FollowCamera를 사용하며, 입력 방향은 컨트롤러 yaw를 기준으로 전후좌우 이동한다."),
    Block(kind: .code, text: "근거: Content/PlayerCharacter/BP_HeroCharacter.uasset, Source/Warrior/Public/Characters/WarriorHeroCharacter.cpp"),
    Block(kind: .body, text: "콘텐츠에는 SK_Hero, SK_CharM_Warrior, SK_CharM_Barbarous가 포함되어 있어 전사형 캐릭터 외형을 사용한다. 애니메이션은 도끼 장착/해제, 걷기, 조깅, 회피, 방어, 약공격 4연속, 강공격 2종, 피격 방향별 리액션, 사망 모션으로 구성되어 있다."),
    Block(kind: .code, text: "근거: Content/Assets/HeroCharacter, Content/PlayerCharacter/Montages"),
    Block(kind: .heading2, text: "플레이어가 할 수 있는 행동"),
    Block(kind: .bullet, text: "• 이동과 시점 조작: IA_Move, IA_Look"),
    Block(kind: .bullet, text: "• 도끼 장착/해제: IA_EquipAxe, IA_UnequipAxe"),
    Block(kind: .bullet, text: "• 도끼 약공격/강공격: IA_LightAttack_Axe, IA_HeavyAttack_Axe"),
    Block(kind: .bullet, text: "• 회피: IA_Roll과 Hero_Roll 애니메이션"),
    Block(kind: .bullet, text: "• 방어: IA_Block, Hero_AxeBlock, StandingBlock 애니메이션"),

    Block(kind: .heading1, text: "3. 조작과 전투 입력"),
    Block(kind: .body, text: "프로젝트의 입력은 Enhanced Input 기반이다. DefaultInput.ini는 기본 입력 컴포넌트로 WarriorInputComponent를 사용하며, PlayerCharacter/Input 폴더에는 이동, 카메라, 도끼 공격, 방어, 회피, 장착/해제 InputAction이 분리되어 있다."),
    Block(kind: .code, text: "근거: Config/DefaultInput.ini, Content/PlayerCharacter/Input/Actions"),
    Block(kind: .body, text: "게임플레이 태그 기준으로 보면 플레이어 입력은 Move, Look, EquipAxe, UnequipAxe, LightAttack.Axe, HeavyAttack.Axe, Roll, Block으로 정리된다. 이 입력들은 Player.Ability.* 계열 어빌리티와 연결된다."),
    Block(kind: .code, text: "근거: Source/Warrior/Public/WarriorGameplayTags.cpp:8-32"),

    Block(kind: .heading1, text: "4. 전투 시스템"),
    Block(kind: .body, text: "전투는 도끼 충돌 박스와 적의 몸/손 충돌 박스를 켜고 끄는 방식으로 타격 구간을 만든다. 공격 애니메이션 중 AnimNotifyState가 무기 충돌을 켜면, 충돌한 적에게 GameplayEvent가 전달되고 해당 어빌리티가 데미지 GameplayEffect를 적용한다."),
    Block(kind: .code, text: "근거: Content/Shared/AnimNotifyState/ANS_ToggleWeaponCollision.uasset, Source/Warrior/Private/Components/Combat"),
    Block(kind: .heading2, text: "공격"),
    Block(kind: .bullet, text: "• 약공격은 AM_Hero_Axe_LightAttack_1~4로 이어지는 콤보 구조다."),
    Block(kind: .bullet, text: "• 강공격은 AM_Hero_Axe_HeavyAttack_1~2와 AxeHeavyAOE 이펙트가 있어 더 큰 타격/범위 공격 성격을 가진다."),
    Block(kind: .bullet, text: "• 타격 시 AxeHit 사운드, 히트 정지, 카메라 셰이크, Niagara Trail/Impact 효과가 사용된다."),
    Block(kind: .heading2, text: "방어"),
    Block(kind: .bullet, text: "• 방어 중 적 공격을 정면에서 받으면 SuccessfulBlock 이벤트가 발생한다."),
    Block(kind: .bullet, text: "• PerfectBlock, MagicShield, BlockImpact 관련 GameplayCue와 사운드/이펙트 에셋이 포함되어 있다."),
    Block(kind: .bullet, text: "• 일부 적 공격은 Enemy.Status.Unblockable 상태로 방어 불가 공격을 표현한다."),
    Block(kind: .heading2, text: "피격과 사망"),
    Block(kind: .bullet, text: "• 피격 방향은 Front, Left, Right, Back 태그로 나뉘며 방향별 히트 리액션 몽타주가 있다."),
    Block(kind: .bullet, text: "• 체력이 0이 되면 Shared.Status.Dead가 붙고 Hero/Enemy Death Ability가 실행되는 구조다."),

    Block(kind: .heading1, text: "5. 능력치와 난이도"),
    Block(kind: .body, text: "캐릭터는 CurrentHealth, MaxHealth, CurrentRage, MaxRage, AttackPower, DefensePower, DamageTaken 속성을 가진다. 플레이어와 적의 시작 능력치는 GE_Hero_StartUp, GE_Hero_Static, GE_Enemy_Static 및 각 적 시작 GameplayEffect로 구성된다."),
    Block(kind: .code, text: "근거: WarriorAttributeSet.h, Content/PlayerCharacter/GameplayEffect, Content/EnemyCharacter/Gruntling/GameplayEffect"),
    Block(kind: .body, text: "난이도는 Easy, Normal, Hard, VeryHard로 나뉘며, 플레이어는 쉬운 난이도일수록 높은 AbilityApplyLevel을 받고 적은 어려운 난이도일수록 높은 레벨을 받는다. 따라서 난이도는 단순 표시가 아니라 실제 어빌리티/효과 레벨에 영향을 준다."),
    Block(kind: .code, text: "근거: WarriorHeroCharacter.cpp, WarriorEnemyCharacter.cpp, WarriorBaseGameMode"),

    Block(kind: .heading1, text: "6. 적 구성"),
    Block(kind: .body, text: "프로젝트에는 일반 적과 보스 성격의 적이 함께 들어 있다. Gruntling 계열은 Guardian과 Glacer로 나뉘며, FrostGiant/Troll 계열은 보스 체력바와 소환, 큰 공격 모션을 가진 적으로 구성되어 있다."),
    Block(kind: .heading2, text: "Guardian"),
    Block(kind: .bullet, text: "• 근접 공격 중심 적이다. GA_Guardian_Melee_1, GA_Guardian_Melee_2, Guardian 무기와 Behavior Tree가 포함되어 있다."),
    Block(kind: .code, text: "근거: Content/EnemyCharacter/Gruntling/Guardian, Content/EnemyCharacter/Gruntling/GameplayAbility"),
    Block(kind: .heading2, text: "Glacer"),
    Block(kind: .bullet, text: "• 근접 공격과 투사체를 함께 가진 적이다. GA_Glacer_Projectile, BP_Projectile_Glacer, Glacer 전용 Trail/StartUp 데이터가 포함되어 있다."),
    Block(kind: .code, text: "근거: Content/EnemyCharacter/Gruntling/Glacer"),
    Block(kind: .heading2, text: "Frost Giant / Troll"),
    Block(kind: .bullet, text: "• 대형 적 또는 보스 역할을 하는 적이다. DrawBossBar, SummonEnemies, 여러 MeleeAttack, Death, HitReact 어빌리티가 있다."),
    Block(kind: .bullet, text: "• Troll/IceGiant 사운드, 대형 타격, 사망, 고통, 함성 계열 사운드가 포함되어 전투 존재감을 강화한다."),
    Block(kind: .code, text: "근거: Content/EnemyCharacter/FrostGiant, Content/Assets/Enemies/Enemy_Troll, Content/Assets/Sounds/Creatures"),

    Block(kind: .heading1, text: "7. 적 AI와 행동"),
    Block(kind: .body, text: "적은 AI Perception으로 플레이어를 감지하고 Blackboard의 TargetActor를 설정한다. Behavior Tree는 감지한 대상을 향해 이동하거나 회전하고, 공격 가능 상황에서 Melee/Ranged/Summon 어빌리티를 실행하는 구조다."),
    Block(kind: .code, text: "근거: WarriorAIController.cpp, Content/EnemyCharacter/BB_Enemy_Base.uasset, BT_Guardian.uasset, BT_Glacer.uasset"),
    Block(kind: .bullet, text: "• 시야 감지: SightRadius 5000, 360도 감지"),
    Block(kind: .bullet, text: "• 팀 구분: AI Controller의 GenericTeamId로 플레이어와 적을 구분"),
    Block(kind: .bullet, text: "• 회전 제어: TargetActor를 향해 보간 회전하는 Behavior Tree Task/Service"),
    Block(kind: .bullet, text: "• 군중 이동: Detour Crowd Avoidance를 통해 다수 적 이동 충돌을 완화"),

    Block(kind: .heading1, text: "8. 웨이브 진행"),
    Block(kind: .body, text: "게임 모드는 웨이브 상태 머신으로 동작한다. 새 웨이브 대기, 적 스폰, 전투 진행, 웨이브 완료, 전체 웨이브 완료, 플레이어 사망 상태가 정의되어 있다."),
    Block(kind: .code, text: "근거: WarriorSurvialGameMode.h:11-20"),
    Block(kind: .body, text: "각 웨이브는 DataTable Row로 정의된다. Row에는 스폰할 적 클래스, 스폰당 최소/최대 수, 해당 웨이브 전체 적 수가 들어간다. 실제 스폰 위치는 맵의 TargetPoint 주변 내비게이션 가능 영역에서 랜덤으로 선택된다."),
    Block(kind: .code, text: "근거: WarriorSurvialGameMode.cpp, DT_EenmyWaveSpawner.uasset"),
    Block(kind: .bullet, text: "• 웨이브 시작 전 5초 대기 시간이 있다."),
    Block(kind: .bullet, text: "• 적 스폰 전 2초 지연이 있다."),
    Block(kind: .bullet, text: "• 웨이브 완료 후 다음 웨이브까지 5초 대기한다."),
    Block(kind: .bullet, text: "• 적이 모두 처치되면 WaveCompleted로 전환된다."),

    Block(kind: .heading1, text: "9. UI와 피드백"),
    Block(kind: .body, text: "UI는 플레이어 오버레이, 적 체력바, 보스 체력바, 웨이브 텍스트, 패배 화면으로 구성된다. 체력과 분노는 AttributeSet 변화 이벤트를 통해 UI에 반영된다."),
    Block(kind: .code, text: "근거: Content/Widgets/HeroWidgets/WBP_HeroOverlay.uasset, Content/Widgets/EnemyWidgets, Content/Widgets/GameModeWidgets"),
    Block(kind: .bullet, text: "• WBP_HeroOverlay: 플레이어 체력/분노/무기 상태를 표시하는 주 UI"),
    Block(kind: .bullet, text: "• WBP_DefaultEnemyHealthBar: 일반 적 체력 표시"),
    Block(kind: .bullet, text: "• WBP_DefaultBossHealthbar: 보스급 적 체력 표시"),
    Block(kind: .bullet, text: "• WBP_WaveTextWithCountDown, WBP_WaveTextNoCountDown: 웨이브 안내"),
    Block(kind: .bullet, text: "• WBP_LoseScreen: 플레이어 사망 시 결과 화면"),
    Block(kind: .body, text: "전투 피드백은 GameplayCue와 Niagara, 사운드로 보강된다. AxeHit, MagicShield, PerfectBlock, SuccessfulBlock, AttackWarning, DeathSound 같은 Cue가 있고, AxeHeavyAOE, Trail, Impact, Dissolve 이펙트가 포함되어 있다."),

    Block(kind: .heading1, text: "10. 플레이 흐름"),
    Block(kind: .body, text: "게임을 시작하면 플레이어는 전사 캐릭터를 조작해 전장에 진입한다. 웨이브 카운트다운 후 적이 TargetPoint 주변에 등장하고, 플레이어는 도끼 장착, 공격, 회피, 방어를 조합해 적을 처치한다. 웨이브의 총 적 수를 모두 처치하면 짧은 대기 후 다음 웨이브가 시작된다."),
    Block(kind: .bullet, text: "• 1단계: 캐릭터 이동과 카메라 조작으로 적 위치 파악"),
    Block(kind: .bullet, text: "• 2단계: 도끼를 장착하고 약공격/강공격으로 적을 압박"),
    Block(kind: .bullet, text: "• 3단계: 적 공격은 회피하거나 정면 방어로 막기"),
    Block(kind: .bullet, text: "• 4단계: 체력과 분노 게이지를 관리하며 웨이브 클리어"),
    Block(kind: .bullet, text: "• 5단계: 보스급 적이 등장하면 보스 체력바와 특수 공격에 대응"),

    Block(kind: .heading1, text: "11. 게임의 특징"),
    Block(kind: .bullet, text: "• 도끼 기반 근접 액션: 약공격 콤보, 강공격, 방어, 회피가 중심이다."),
    Block(kind: .bullet, text: "• 웨이브 서바이벌 구조: DataTable 기반으로 웨이브별 적 구성이 바뀐다."),
    Block(kind: .bullet, text: "• 다양한 적 타입: Guardian, Glacer, Frost Giant/Troll 계열 적이 다른 공격 성격을 가진다."),
    Block(kind: .bullet, text: "• 명확한 전투 피드백: 히트 정지, 카메라 셰이크, Niagara 이펙트, 사운드, 체력바가 결합된다."),
    Block(kind: .bullet, text: "• 방어 판정: 정면 방어, 성공 방어, 완벽 방어, 방어 불가 공격으로 전투 리듬을 만든다."),
    Block(kind: .bullet, text: "• 난이도 스케일링: 플레이어와 적의 어빌리티 적용 레벨이 난이도에 따라 달라진다.")
]

var mediaBox = CGRect(x: 0, y: 0, width: pageWidth, height: pageHeight)
let data = NSMutableData()
guard let consumer = CGDataConsumer(data: data as CFMutableData),
      let context = CGContext(consumer: consumer, mediaBox: &mediaBox, nil) else {
    fatalError("Could not create PDF context")
}

var pageNumber = 0
var y = marginTop

func pdfRect(topX x: CGFloat, topY y: CGFloat, width: CGFloat, height: CGFloat) -> CGRect {
    CGRect(x: x, y: pageHeight - y - height, width: width, height: height)
}

func drawPageHeaderFooter() {
    let headerText = NSAttributedString(
        string: "Warrior 게임 설명서",
        attributes: [.font: font(8.5), .foregroundColor: muted]
    )
    headerText.draw(in: pdfRect(topX: marginX, topY: 24, width: contentWidth, height: 16))

    rule.setStroke()
    let path = NSBezierPath()
    let ruleY = pageHeight - 43
    path.move(to: CGPoint(x: marginX, y: ruleY))
    path.line(to: CGPoint(x: pageWidth - marginX, y: ruleY))
    path.lineWidth = 0.6
    path.stroke()

    let footer = NSAttributedString(
        string: "\(pageNumber)",
        attributes: [.font: font(8.5), .foregroundColor: muted]
    )
    footer.draw(in: pdfRect(topX: marginX, topY: pageHeight - 34, width: contentWidth, height: 14))
}

func beginPage() {
    pageNumber += 1
    context.beginPDFPage(nil)
    NSGraphicsContext.current = NSGraphicsContext(cgContext: context, flipped: false)
    NSColor.white.setFill()
    NSBezierPath(rect: CGRect(x: 0, y: 0, width: pageWidth, height: pageHeight)).fill()
    drawPageHeaderFooter()
    y = marginTop
}

func endPage() {
    context.endPDFPage()
}

func drawBlock(_ block: Block) {
    let blockHeight = measuredHeight(block, width: contentWidth)
    if y + blockHeight > pageHeight - marginBottom {
        endPage()
        beginPage()
    }

    if block.kind == .heading1 {
        y += 6
        accent.setFill()
        NSBezierPath(roundedRect: pdfRect(topX: marginX, topY: y + 2, width: 4, height: 20), xRadius: 1.5, yRadius: 1.5).fill()
    }

    if block.kind == .code {
        pale.setFill()
        NSBezierPath(roundedRect: pdfRect(topX: marginX - 6, topY: y - 2, width: contentWidth + 12, height: blockHeight - 3), xRadius: 5, yRadius: 5).fill()
    }

    let x = block.kind == .heading1 ? marginX + 12 : marginX
    let width = block.kind == .heading1 ? contentWidth - 12 : contentWidth
    let attributed = NSAttributedString(string: block.text, attributes: attributes(for: block.kind))
    attributed.draw(in: pdfRect(topX: x, topY: y, width: width, height: blockHeight))
    y += blockHeight
}

beginPage()
for block in blocks {
    drawBlock(block)
}
endPage()
context.closePDF()

let outputURL = URL(fileURLWithPath: outputPath)
try FileManager.default.createDirectory(at: outputURL.deletingLastPathComponent(), withIntermediateDirectories: true)
try data.write(to: outputURL, options: .atomic)
print(outputURL.path)
