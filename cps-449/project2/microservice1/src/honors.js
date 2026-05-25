/**
 * Information sourced from:
 * https://catalog.udayton.edu/undergraduate/generalinformation/academicinformation/honors/
 *
 * Notes:
 * - GPA thresholds here are intentionally modeled as ordered range checks.
 * - 60 total earned credits is enforced as the hard minimum for honors.
 */

const HONORS_TIER_RULES = [
    { name: 'Summa Cum Laude', minGpa: 3.9 },
    { name: 'Magna Cum Laude', minGpa: 3.7 },
    { name: 'Cum Laude', minGpa: 3.5 }
];

// UDayton-style honor floors; all tiers require this credit minimum.
const MIN_CREDITS_FOR_HONORS = 60;

// Keep output stable for presentation and avoids floating point artifacts in clients.
function roundTwoDecimals(value) {
    return Number(value.toFixed(2));
}

// Parse credit input from route/query/body callers into an integer or a structured error.
// Returns null when credits were not provided (allowed by API for partial input checks).
function parseCredits(value) {
    if (value === undefined) return null;

    const credits = Number(value);

    if (!Number.isInteger(credits) || credits < 0) {
        return {
            error: 'Credits must be a non-negative integer.'
        };
    }

    return credits;
}

function getNextHonorsGoal(gpa) {
    // Ordered from lowest to highest in HONORS_TIER_RULES.
    // Reverse to find the first "next tier above current GPA" for progress messaging.
    const orderedTiers = [...HONORS_TIER_RULES].reverse();
    const next = orderedTiers.find(tier => gpa < tier.minGpa);

    if (!next) {
        return null;
    }

    const gpaIncrease = roundTwoDecimals(next.minGpa - gpa);

    return {
        nextTier: next.name,
        targetGpa: next.minGpa,
        gpaIncrease,
        message: `Raise GPA by ${gpaIncrease} to reach ${next.name}.`
    };
}

function assessAcademicRisk(gpa, credits) {
    // risk model intentionally uses credit milestones as a confidence gate first, then GPA bands.
    if (credits === null) {
        return {
            level: 'unknown',
            summary: 'Add credits parameter for a stronger forecast.'
        };
    }

    if (credits < 30) {
        return {
            level: 'limited',
            summary: 'Less than 30 credits: risk is preliminary and can shift quickly.'
        };
    }

    if (credits < MIN_CREDITS_FOR_HONORS) {
        return {
            level: 'limited',
            summary: 'Less than 60 credits: Latin honors are not yet available.'
        };
    }

    if (gpa >= 3.7) {
        return {
            level: 'low',
            summary: 'Strong momentum; likely to hold current standing with current workload.'
        };
    }

    if (gpa >= 3.2) {
        return {
            level: 'medium',
            summary: 'Moderate risk. Small GPA declines can affect honors qualification.'
        };
    }

    if (gpa >= 2.0) {
        return {
            level: 'medium-high',
            summary: 'Good standing but not close to honors thresholds. Prioritize improvement.'
        };
    }

    return {
        level: 'high',
        summary: 'At/under probation threshold; immediate academic recovery is advised.'
    };
}

function buildMessage(gpa, honors, creditsMet, nextHonors, academicRisk, credits) {
    if (honors !== 'None') {
        return `Eligible for ${honors}.`;
    }

    if (gpa >= 3.5 && credits !== null && !creditsMet) {
        return `You have GPA-level honors potential, but require at least ${MIN_CREDITS_FOR_HONORS} credits to qualify.`;
    }

    if (!creditsMet && credits !== null && gpa < 3.5) {
        return `Raise your GPA to at least 3.50 and earn ${MIN_CREDITS_FOR_HONORS} credits for Latin honors.`;
    }

    if (nextHonors) {
        return nextHonors.message;
    }

    if (credits === null) {
        return 'Provide credits for an accurate eligibility recommendation.';
    }

    return 'Current profile is below Latin honors thresholds.';
}

// Build one concise recommendation line so responses are easier to read in the UI.
function getHonors(gpaInput, creditsInput) {
    const gpa = Number(gpaInput);

    if (!Number.isFinite(gpa) || gpa < 0 || gpa > 4) {
        return {
            error: 'Please provide a valid GPA between 0 and 4.'
        };
    }

    const credits = parseCredits(creditsInput);
    if (credits !== null && credits.error) {
        return credits;
    }

    const creditsMet = credits !== null && credits >= MIN_CREDITS_FOR_HONORS;
    let honors = 'None';

    // Honors are only assigned when both GPA threshold and credit threshold are satisfied.
    if (creditsMet) {
        if (gpa >= 3.9) {
            honors = 'Summa Cum Laude';
        } else if (gpa >= 3.7) {
            honors = 'Magna Cum Laude';
        } else if (gpa >= 3.5) {
            honors = 'Cum Laude';
        }
    }

    const status = gpa >= 2.0 ? 'In Good Standing' : 'Academic Probation';
    const nextHonors = getNextHonorsGoal(gpa);
    const academicRisk = assessAcademicRisk(gpa, credits);
    const message = buildMessage(gpa, honors, creditsMet, nextHonors, academicRisk, credits);

    return {
        gpa: roundTwoDecimals(gpa),
        credits,
        honors,
        status,
        deltaToNextHonors: nextHonors,
        academicRisk,
        message
    };
}

// Return the honor table in a shape that avoids accidental mutation from callers.
function getHonorsTiers() {
    return HONORS_TIER_RULES.map(tier => ({ ...tier }));
}

module.exports = {
    getHonors,
    getHonorsTiers
};
